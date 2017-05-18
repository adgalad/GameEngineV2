//
//  Scene.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Game.hpp"
#include "Object.hpp"

using namespace engine;

inline bool hasToBeRemoved(Object *obj) {
	return obj->deleted;
}


template<class T>
Rect Camera<T>::getCameraRect() {
  
	Vector2 v = Application.renderer()->getWindowSize();
	rect = Rect(  0, 0
							, min((int)v.x,sceneRect.w)
							, min((int)v.y,sceneRect.h));

	Rect cameraRect = rect;

	if (target){
		Vector2 p  = target->transform.position;
		Rect r      = target->texture->getRect();
		Vector2 ss = Application.renderer()->getWindowSize();
		/*
		 Mueve la camara si el target esta en el centro de la pantalla.
		 CameraRect siempre debe tener campos positivos, de lo contrario
		 distorciona la imagen
			*/
		if (p.x > 0){
			cameraRect.x += p.x - (ss.x - r.w)/2;
			if ( cameraRect.x < 0) cameraRect.x = 0;
		}
		if (p.y > 0){
			cameraRect.y += p.y - (ss.y - r.h)/2;
			if ( cameraRect.y < 0) cameraRect.y = 0;
		}
		
	}
	if (cameraRect.x + rect.w > sceneRect.w)
	{
		cameraRect.x = sceneRect.w - rect.w;
	}
	if (cameraRect.y + rect.h > sceneRect.h)
	{
		cameraRect.y = sceneRect.h - rect.h;
	}
	return cameraRect;
}



Scene::Scene(){};

Scene::Scene (string name, Rect size){

	this->name = name;
	Rect cameraSize;
//	Vector2 v = Application.renderer()->getWindowSize();
	camera.setSceneSize(size);
  if (size == Rect(0,0,0,0)){
//      camera.setCameraRect(Rect(0,0,v.x,v.y));
    camera.setCameraRect(Rect(0,0,0,0));
  } else {
    camera.setCameraRect(size);
  }
	
}

Scene::~Scene(){
	for (int i = 0; i < objs.size(); ++i){
		delete objs[i];
	}
	delete background;
}

void Scene::addObject(Object *object) {
	objs.push_back(object);
	object->scene = this;
}




void Scene::Init(){
  
  _target_texture = new Texture();
  _target_texture->createTargetTexture("Target Texture Scene "+name, camera.sceneRect);
  
	Start();
	for (int i  = 0 ; i < objs.size(); i ++){
		objs[i]->Init();
	}
  
}

void Scene::Reset(){
	for (int i  = 0 ; i < objs.size(); i ++){
		objs[i]->reset();
	}
}



void Scene::Start(){
//	camera.setCameraRect(Rect(30,30,300,300));
	if (not _target_texture) {
		if (objs.size() > 0 and objs[0]->texture) {
			_target_texture = objs[0]->texture.get();
      _target_texture->setAsRenderTarget();
      Application.renderer()->clearRender();
		}
    else {
      error("Could not initialize Scene Target Texture");
    }
  } else {
//    _target_texture->setAsRenderTarget();
//    Application.renderer()->clearRender();
  }
}

void Scene::Update(){}

void Scene::InternalUpdate(){
  Update();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->InternalUpdate();
    _hasObjectToRemove |= objs[i]->deleted;
  }
  
  if (_hasObjectToRemove) {
    objs.erase(remove_if(objs.begin(), objs.end(), hasToBeRemoved), objs.end());
  }
  _hasObjectToRemove = false;
}

void Scene::clearTargetAfterRender(bool b){
  _clearRender = b;
}

void Scene::InternalRender(){
  
  if (background){
    background->Render(Vector2(0,0));
  }
  Render();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->Render();
  }
  
  AfterRender();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->AfterRender();
  }
  Application.renderer()->setRendererTarget(NULL);
  Rect srcRect = camera.getCameraRect();

  Vector2 pos   = Vector2(0,0)
         , scale = Vector2(1,1);
  _target_texture->Render(pos, scale, &srcRect);
  _target_texture->setAsRenderTarget();
  
  if (_clearRender) Application.renderer()->clearRender();

}
void Scene::Render(){}

void Scene::AfterRender(){}

EXPORT_IMPLEMENT(Scene);
EXPORT_IMPLEMENT(Object);
EXPORT_IMPLEMENT(ObjectModule);






















//
//
//
///* Information about the current video settings. */
//const SDL_VideoInfo* info = NULL;
///* Dimensions of our window. */
//int width = 0;
//int height = 0;
///* Color depth in bits of our window. */
//int bpp = 0;
///* Flags we will pass into SDL_SetVideoMode. */
//int flags = 0;
//
///* First, initialize SDL's video subsystem. */
//if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
//  /* Failed, exit. */
//  fprintf( stderr, "Video initialization failed: %s\n",
//          SDL_GetError( ) );
//  quit_tutorial( 1 );
//}
//
///* Let's get some video information. */
//info = SDL_GetVideoInfo( );
//
//if( !info ) {
//  /* This should probably never happen. */
//  fprintf( stderr, "Video query failed: %s\n",
//          SDL_GetError( ) );
//  quit_tutorial( 1 );
//}
//
///*
// * Set our width/height to 640/480 (you would
// * of course let the user decide this in a normal
// * app). We get the bpp we will request from
// * the display. On X11, VidMode can't change
// * resolution, so this is probably being overly
// * safe. Under Win32, ChangeDisplaySettings
// * can change the bpp.
// */
//width = 640;
//height = 480;
//bpp = info->vfmt->BitsPerPixel;
//
///*
// * Now, we want to setup our requested
// * window attributes for our OpenGL window.
// * We want *at least* 5 bits of red, green
// * and blue. We also want at least a 16-bit
// * depth buffer.
// *
// * The last thing we do is request a double
// * buffered window. '1' turns on double
// * buffering, '0' turns it off.
// *
// * Note that we do not use SDL_DOUBLEBUF in
// * the flags to SDL_SetVideoMode. That does
// * not affect the GL attribute state, only
// * the standard 2D blitting setup.
// */
//SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
//SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
//SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
//SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
//SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
//
///*
// * We want to request that SDL provide us
// * with an OpenGL window, in a fullscreen
// * video mode.
// *
// * EXERCISE:
// * Make starting windowed an option, and
// * handle the resize events properly with
// * glViewport.
// */
//flags = SDL_OPENGL | SDL_FULLSCREEN;
//
///*
// * Set the video mode
// */
//if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
//  /*
//   * This could happen for a variety of reasons,
//   * including DISPLAY not being set, the specified
//   * resolution not being available, etc.
//   */
//  fprintf( stderr, "Video mode set failed: %s\n",
//          SDL_GetError( ) );
//  quit_tutorial( 1 );
//}
//Drawing
//
//Apart from initialisation, using OpenGL within SDL is the same as using OpenGL with any other API, e.g. GLUT. You still use all the same function calls and data types. However if you are using a double-buffered display, then you must use SDL_GL_SwapBuffers() to swap the buffers and update the display. To request double-buffering with OpenGL, use SDL_GL_SetAttribute with SDL_GL_DOUBLEBUFFER, and use SDL_GL_GetAttribute to see if you actually got it.
//
//A full example code listing is now presented below.
//
//Example 2-8. SDL and OpenGL
//
///*
// * SDL OpenGL Tutorial.
// * (c) Michael Vance, 2000
// * briareos@lokigames.com
// *
// * Distributed under terms of the LGPL.
// */
//
//#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//
//#include <stdio.h>
//#include <stdlib.h>
//
//static GLboolean should_rotate = GL_TRUE;
//
//static void quit_tutorial( int code )
//{
//  /*
//   * Quit SDL so we can release the fullscreen
//   * mode and restore the previous video settings,
//   * etc.
//   */
//  SDL_Quit( );
//  
//  /* Exit program. */
//  exit( code );
//}
//
//static void handle_key_down( SDL_keysym* keysym )
//{
//  
//  /*
//   * We're only interested if 'Esc' has
//   * been presssed.
//   *
//   * EXERCISE:
//   * Handle the arrow keys and have that change the
//   * viewing position/angle.
//   */
//  switch( keysym->sym ) {
//    case SDLK_ESCAPE:
//      quit_tutorial( 0 );
//      break;
//    case SDLK_SPACE:
//      should_rotate = !should_rotate;
//      break;
//    default:
//      break;
//  }
//  
//}
//
//static void process_events( void )
//{
//  /* Our SDL event placeholder. */
//  SDL_Event event;
//  
//  /* Grab all the events off the queue. */
//  while( SDL_PollEvent( &event ) ) {
//    
//    switch( event.type ) {
//      case SDL_KEYDOWN:
//        /* Handle key presses. */
//        handle_key_down( &event.key.keysym );
//        break;
//      case SDL_QUIT:
//        /* Handle quit requests (like Ctrl-c). */
//        quit_tutorial( 0 );
//        break;
//    }
//    
//  }
//  
//}
//
//static void draw_screen( void )
//{
//  /* Our angle of rotation. */
//  static float angle = 0.0f;
//  
//  /*
//   * EXERCISE:
//   * Replace this awful mess with vertex
//   * arrays and a call to glDrawElements.
//   *
//   * EXERCISE:
//   * After completing the above, change
//   * it to use compiled vertex arrays.
//   *
//   * EXERCISE:
//   * Verify my windings are correct here ;).
//   */
//  static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
//  static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
//  static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
//  static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
//  static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
//  static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
//  static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
//  static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
//  static GLubyte red[]    = { 255,   0,   0, 255 };
//  static GLubyte green[]  = {   0, 255,   0, 255 };
//  static GLubyte blue[]   = {   0,   0, 255, 255 };
//  static GLubyte white[]  = { 255, 255, 255, 255 };
//  static GLubyte yellow[] = {   0, 255, 255, 255 };
//  static GLubyte black[]  = {   0,   0,   0, 255 };
//  static GLubyte orange[] = { 255, 255,   0, 255 };
//  static GLubyte purple[] = { 255,   0, 255,   0 };
//  
//  /* Clear the color and depth buffers. */
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//  
//  /* We don't want to modify the projection matrix. */
//  glMatrixMode( GL_MODELVIEW );
//  glLoadIdentity( );
//  
//  /* Move down the z-axis. */
//  glTranslatef( 0.0, 0.0, -5.0 );
//  
//  /* Rotate. */
//  glRotatef( angle, 0.0, 1.0, 0.0 );
//  
//  if( should_rotate ) {
//    
//    if( ++angle > 360.0f ) {
//      angle = 0.0f;
//    }
//    
//  }
//  
//  /* Send our triangle data to the pipeline. */
//  glBegin( GL_TRIANGLES );
//  
//  glColor4ubv( red );
//  glVertex3fv( v0 );
//  glColor4ubv( green );
//  glVertex3fv( v1 );
//  glColor4ubv( blue );
//  glVertex3fv( v2 );
//  
//  glColor4ubv( red );
//  glVertex3fv( v0 );
//  glColor4ubv( blue );
//  glVertex3fv( v2 );
//  glColor4ubv( white );
//  glVertex3fv( v3 );
//  
//  glColor4ubv( green );
//  glVertex3fv( v1 );
//  glColor4ubv( black );
//  glVertex3fv( v5 );
//  glColor4ubv( orange );
//  glVertex3fv( v6 );
//  
//  glColor4ubv( green );
//  glVertex3fv( v1 );
//  glColor4ubv( orange );
//  glVertex3fv( v6 );
//  glColor4ubv( blue );
//  glVertex3fv( v2 );
//  
//  glColor4ubv( black );
//  glVertex3fv( v5 );
//  glColor4ubv( yellow );
//  glVertex3fv( v4 );
//  glColor4ubv( purple );
//  glVertex3fv( v7 );
//  
//  glColor4ubv( black );
//  glVertex3fv( v5 );
//  glColor4ubv( purple );
//  glVertex3fv( v7 );
//  glColor4ubv( orange );
//  glVertex3fv( v6 );
//  
//  glColor4ubv( yellow );
//  glVertex3fv( v4 );
//  glColor4ubv( red );
//  glVertex3fv( v0 );
//  glColor4ubv( white );
//  glVertex3fv( v3 );
//  
//  glColor4ubv( yellow );
//  glVertex3fv( v4 );
//  glColor4ubv( white );
//  glVertex3fv( v3 );
//  glColor4ubv( purple );
//  glVertex3fv( v7 );
//  
//  glColor4ubv( white );
//  glVertex3fv( v3 );
//  glColor4ubv( blue );
//  glVertex3fv( v2 );
//  glColor4ubv( orange );
//  glVertex3fv( v6 );
//  
//  glColor4ubv( white );
//  glVertex3fv( v3 );
//  glColor4ubv( orange );
//  glVertex3fv( v6 );
//  glColor4ubv( purple );
//  glVertex3fv( v7 );
//  
//  glColor4ubv( green );
//  glVertex3fv( v1 );
//  glColor4ubv( red );
//  glVertex3fv( v0 );
//  glColor4ubv( yellow );
//  glVertex3fv( v4 );
//  
//  glColor4ubv( green );
//  glVertex3fv( v1 );
//  glColor4ubv( yellow );
//  glVertex3fv( v4 );
//  glColor4ubv( black );
//  glVertex3fv( v5 );
//  
//  glEnd( );
//  
//  /*
//   * EXERCISE:
//   * Draw text telling the user that 'Spc'
//   * pauses the rotation and 'Esc' quits.
//   * Do it using vetors and textured quads.
//   */
//  
//  /*
//   * Swap the buffers. This this tells the driver to
//   * render the next frame from the contents of the
//   * back-buffer, and to set all rendering operations
//   * to occur on what was the front-buffer.
//   *
//   * Double buffering prevents nasty visual tearing
//   * from the application drawing on areas of the
//   * screen that are being updated at the same time.
//   */
//  SDL_GL_SwapBuffers( );
//}
//
//static void setup_opengl( int width, int height )
//{
//  float ratio = (float) width / (float) height;
//  
//  /* Our shading model--Gouraud (smooth). */
//  glShadeModel( GL_SMOOTH );
//  
//  /* Culling. */
//  glCullFace( GL_BACK );
//  glFrontFace( GL_CCW );
//  glEnable( GL_CULL_FACE );
//  
//  /* Set the clear color. */
//  glClearColor( 0, 0, 0, 0 );
//  
//  /* Setup our viewport. */
//  glViewport( 0, 0, width, height );
//  
//  /*
//   * Change to the projection matrix and set
//   * our viewing volume.
//   */
//  glMatrixMode( GL_PROJECTION );
//  glLoadIdentity( );
//  /*
//   * EXERCISE:
//   * Replace this with a call to glFrustum.
//   */
//  gluPerspective( 60.0, ratio, 1.0, 1024.0 );
//}
//
//int main( int argc, char* argv[] )
//{
//  /* Information about the current video settings. */
//  const SDL_VideoInfo* info = NULL;
//  /* Dimensions of our window. */
//  int width = 0;
//  int height = 0;
//  /* Color depth in bits of our window. */
//  int bpp = 0;
//  /* Flags we will pass into SDL_SetVideoMode. */
//  int flags = 0;
//  
//  /* First, initialize SDL's video subsystem. */
//  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
//    /* Failed, exit. */
//    fprintf( stderr, "Video initialization failed: %s\n",
//            SDL_GetError( ) );
//    quit_tutorial( 1 );
//  }
//  
//  /* Let's get some video information. */
//  info = SDL_GetVideoInfo( );
//  
//  if( !info ) {
//    /* This should probably never happen. */
//    fprintf( stderr, "Video query failed: %s\n",
//            SDL_GetError( ) );
//    quit_tutorial( 1 );
//  }
//  
//  /*
//   * Set our width/height to 640/480 (you would
//   * of course let the user decide this in a normal
//   * app). We get the bpp we will request from
//   * the display. On X11, VidMode can't change
//   * resolution, so this is probably being overly
//   * safe. Under Win32, ChangeDisplaySettings
//   * can change the bpp.
//   */
//  width = 640;
//  height = 480;
//  bpp = info->vfmt->BitsPerPixel;
//  
//  /*
//   * Now, we want to setup our requested
//   * window attributes for our OpenGL window.
//   * We want *at least* 5 bits of red, green
//   * and blue. We also want at least a 16-bit
//   * depth buffer.
//   *
//   * The last thing we do is request a double
//   * buffered window. '1' turns on double
//   * buffering, '0' turns it off.
//   *
//   * Note that we do not use SDL_DOUBLEBUF in
//   * the flags to SDL_SetVideoMode. That does
//   * not affect the GL attribute state, only
//   * the standard 2D blitting setup.
//   */
//  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
//  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
//  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
//  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
//  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
//  
//  /*
//   * We want to request that SDL provide us
//   * with an OpenGL window, in a fullscreen
//   * video mode.
//   *
//   * EXERCISE:
//   * Make starting windowed an option, and
//   * handle the resize events properly with
//   * glViewport.
//   */
//  flags = SDL_OPENGL | SDL_FULLSCREEN;
//  
//  /*
//   * Set the video mode
//   */
//  if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
//    /*
//     * This could happen for a variety of reasons,
//     * including DISPLAY not being set, the specified
//     * resolution not being available, etc.
//     */
//    fprintf( stderr, "Video mode set failed: %s\n",
//            SDL_GetError( ) );
//    quit_tutorial( 1 );
//  }
//  
//  /*
//   * At this point, we should have a properly setup
//   * double-buffered window for use with OpenGL.
//   */
//  setup_opengl( width, height );
//  
//  /*
//   * Now we want to begin our normal app process--
//   * an event loop with a lot of redrawing.
//   */
//  while( 1 ) {
//    /* Process incoming events. */
//    process_events( );
//    /* Draw the screen. */
//    draw_screen( );
//  }
//  
//  /*
//   * EXERCISE:
//   * Record timings using SDL_GetTicks() and
//   * and print out frames per second at program
//   * end.
//   */
//  
//  /* Never reached. */
//  return 0;
//}
//Prev	Home	Next
//Graphics and Video	Up	Input handling
