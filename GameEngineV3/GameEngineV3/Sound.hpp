//
//  Sound.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Sound_hpp
#define Sound_hpp

#include "GE_SDL.hpp"
namespace engine {
class Sound {
public:
	
	Sound(){
		
	}
	
	~Sound(){
		Mix_FreeChunk(_chunk);
	}
	
	inline bool loadSound(string file){
		_chunk = Mix_LoadWAV(file.c_str());
		if (_chunk == NULL) {
			error("Warning: Could not load Sound: "+file);
			return false;
		}
		return true;
	}
	
	inline void play(int loop){
		Mix_PlayChannel(_channel, _chunk, loop);
	}
	
	inline void pause(){
		if (_channel < 0){
			error("Warning: Can not pause a sound that has not a specific channel.\nUse setChannel().");
		}
		else if (not Mix_Paused(_channel)){
			Mix_Pause(_channel);
		}
	}
	
	inline void resume() {
		if (_channel < 0){
			error("Warning: Can not resume a sound that has not a specific channel.\nUse setChannel().");
		}
		else if (Mix_Paused(_channel)){
			Mix_Resume(_channel);
		}
	}
	
	inline void setChannel(int channel) {
		if (channel >= 0 and channel < _numChannel){
			_channel = channel;
		} else {
			error("Warning: Channel "+to_string(channel)+" doesn't exists");
		}
	}
	
	inline void setFirstChannelAvailible(){
		_channel = -1;
	}
	
	inline static void Init() {
		_current_music = NULL;
		Mix_AllocateChannels(16);
	}
	
	inline static void AllocateChannels(int numChannels){
		Mix_AllocateChannels(numChannels);
		_numChannel = numChannels;
	}
	
	inline static void PlayMusic(string music, int loop){
		_current_music = Mix_LoadMUS(music.c_str());
		Mix_PlayMusic(_current_music, loop);
	}
	
	inline static void Quit(){
		Mix_FreeMusic(_current_music);
	}
	
private:
	
	static Mix_Music *_current_music; /**< Only one Music can be reproduced at time.
									       If another music is loaded, the
									       previous one is freed. */
	
	static int        _numChannel;    /**< Number of channels currently allocated. */
	
	Mix_Chunk        *_chunk = NULL;  /**< Raw info of the sound file. */
	
	int               _channel = -1;  /**< Channel where the sound will be played,
									       -1 means the first channel availible. */

	
};
}
#endif /* Sound_hpp */
