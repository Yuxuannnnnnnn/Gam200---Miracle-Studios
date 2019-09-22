///////////////////////////////////////////////////////////////////////////////////////
//
//	Collider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

enum ColliderType{
    
    NONE_COLLIDER,
    BOX_COLLIDER,
    CIRCLE_COLLIDER
    
  };

class Collider2D {
public:
  
  Collider2D() : _type{NONE_COLLIDER}, _id{0} {}
  virtual ~Collider2D() {}
  
  ColliderType _type;
  size_t _id;
};




#endif
