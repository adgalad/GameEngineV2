//
//  main.m
//  Editor
//
//  Created by Carlos Spaggiari Roa on 9/6/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "Game.hpp"
int main(int argc, const char * argv[]) {
  NSWindow *window = (__bridge NSWindow*)Cocoa_Game_Window();
  NSSplitView *split = [[NSSplitView alloc] initWithFrame:NSMakeRect(0, 0, 512, 512)];

  
//  [split addArrangedSubview:window.contentView];
//  window.contentView setSuper = split;
  
  NSButton *b = [NSButton buttonWithTitle:@"Hola" target:nil action:nil];
  
  [[[window contentView] subviews][0] addSubview:b];
  Cocoa_Game_Run();
//  return NSApplicationMain(argc, argv);
}
