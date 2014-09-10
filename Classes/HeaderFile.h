//
//  HeaderFile.h
//  UICoordinate
//
//  Created by dzp on 14-7-7.
//
//

#ifndef __UICoordinate__HeaderFile__
#define __UICoordinate__HeaderFile__

//获取屏幕的尺寸
#define WinSize Director::getInstance()->getWinSize()

//鼠标的尺寸大小
#define MouseVec2 Vec2(15,20)

//定义各布局的尺寸大小
#define Top_parent_Height 60
#define Top_line_height 2
#define Top_inputX_vec2 Size(80,3*Top_parent_Height/4)
#define Left_parent_Width 300
#define Left_parent_Height (WinSize.height-Top_parent_Height-Top_line_height)
#define Left_item_height 60
#define Left_pic_width 50
#define Left_pic_height 50
#define Middle_parent_width (WinSize.width-Left_parent_Width-Top_line_height)
#define Middle_parent_height (WinSize.height-Top_parent_Height-Top_line_height)
#define Middle_inputBox_size Size(120,22)
#define Middle_space_height 100
#define Middle_choose_bg_Size Size(200,200)


//设置各个布局的TAG
#define Top_parent_Tag 1
#define Top_inputBox_tag 2
#define Top_sure_tag 3
#define Left_parent_Tag 10002
#define Left_sprite_tag 100
#define Left_scroll_tag 9
#define Middle_parent_Tag 11
#define Middle_spriteX_tag 12
#define Middle_spriteY_tag 13
#define Middle_spriteW_tag 14
#define Middle_spriteH_tag 15
#define Middle_inputX_tag 16
#define Middle_inputY_tag 17
#define Middle_inputW_tag 18
#define Middle_inputH_tag 19
#define Middle_start_tag 20
#define Middle_choose_bg_tag 21
#define Middle_debug_tag 22


#define UIWORK_BG_TAG 1
#define UIWORK_PANEL_TAG 2
#define UIWORK_TESTDEBUG_TAG 3
#define UIWORK_TESTDEBUG_LABEL_TAG 1
#define UIWORK_ZUOBIAO_TAG 100
#define UIWORK_ZUOBIAO_LABEL_TAG 1







/*******************************/
/*用户存储数据的key*/
#define USERPATH "USERPATH"
#define ORIGIN_X "ORIGIN_X"
#define ORIGIN_Y "ORIGIN_Y"
#define OPENGL_WIDTH "OPENGL_WIDTH"
#define OPENGL_HEIGHT "OPENGL_HEIGHT"
#define ISDEBUG "ISDEBUG"

 



#endif /* defined(__UICoordinate__HeaderFile__) */
