//
//  ViewController.m
//  Editor
//
//  Created by Carlos Spaggiari Roa on 9/6/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#import "ViewController.h"


@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  
}

- (void)viewWillAppear {
  NSWindow *window = (__bridge NSWindow*)Cocoa_Game_Window();
  
  
  NSSplitView *splitview = [[NSSplitView alloc] init];
  NSView *mainView = [[NSView alloc] init];
  NSView *rightView = [[NSView alloc] init];
  NSView *leftView  = window.contentView;
  window.menu = [[[self view] window] menu];
  [mainView addSubview:splitview];
  NSLayoutConstraint *contraint = [NSLayoutConstraint
                                   constraintWithItem: splitview
                                   attribute:NSLayoutAttributeCenterX
                                   relatedBy:NSLayoutRelationEqual
                                   toItem: mainView
                                   attribute:NSLayoutAttributeCenterX
                                   multiplier:1.0
                                   constant:0];
  
  [splitview addArrangedSubview:rightView];
  [splitview addArrangedSubview:leftView];
  NSLog(@"\n >>>> %@ \n",splitview.subviews);
  [splitview addConstraint:contraint];
  window.contentView = mainView;
  [[[self view] window] addTabbedWindow:window ordered:NSWindowAbove];
  
  Cocoa_Game_Run();
}


- (void)setRepresentedObject:(id)representedObject {
  [super setRepresentedObject:representedObject];

  // Update the view, if already loaded.
}


@end
