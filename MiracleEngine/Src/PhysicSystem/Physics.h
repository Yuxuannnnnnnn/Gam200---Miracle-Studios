///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H
#include "PrecompiledHeaders.h"

#include "CircleCollider2D.h"
#include "BoxCollider2D.h"

#include<iostream>
#include<vector>
#include<iterator>

class Physics final
{
	//Dynamic array of GameObjects
	std::vector<Collider2D*> _ListCollider2D;
  
  size_t _count;
  
public:
	//No replication of class object
	Physics(const Physics& rhs) = delete;
	Physics& operator= (const Physics& rhs) = delete;

	Physics() :_ListCollider2D{}, _count{0}
	{}

	//Deletes all gameObjects in the list
	~Physics() 
	{
		std::vector<Collider2D*>::iterator iterator = _ListCollider2D.begin();
		while (iterator != _ListCollider2D.end())
		{
			delete *iterator;
			iterator++;
		}
	}
  
  void Update(double dt)
  {
    (void)dt;
    
    std::cout << "~~~~~~~~~~~~~~~~~~" <<std::endl;
    
    std::vector<Collider2D*>::iterator iterator = _ListCollider2D.begin(); 
    
		while (iterator != _ListCollider2D.end())
		{
      if((*iterator)->_type == NONE_COLLIDER)
      {
        iterator++;
        continue;
      }
      
			std::vector<Collider2D*>::iterator iterator2 = _ListCollider2D.begin();
      while (iterator2 != _ListCollider2D.end())
      {
        if(iterator == iterator2 || (*iterator2)->_type == NONE_COLLIDER )
        {
          iterator2++;
          continue;
        }     
        
        if((*iterator)->_type == BOX_COLLIDER)
        {
          BoxCollider2D* aabb = dynamic_cast<BoxCollider2D*>(*iterator);
          
          if((*iterator2)->_type == BOX_COLLIDER)
          {
            BoxCollider2D* aabb2 = dynamic_cast<BoxCollider2D*>(*iterator2);
            
            if(aabb->TestBCVsBC(*aabb2))
              std::cout << "AABB (" << aabb->_id << ") collided with AABB ("<< aabb2->_id <<")." <<std::endl;
          }
          else if((*iterator2)->_type == CIRCLE_COLLIDER)
          {
            CircleCollider2D* circle = dynamic_cast<CircleCollider2D*>(*iterator2);
            
            if(TestCCVsBC(*circle, *aabb))
              std::cout << "AABB (" << aabb->_id << ") collided with Circle ("<< circle->_id <<")." <<std::endl;
          }
        }
        else if((*iterator)->_type == CIRCLE_COLLIDER)
        {
          CircleCollider2D* circle = dynamic_cast<CircleCollider2D*>(*iterator);
          
          if((*iterator2)->_type == BOX_COLLIDER)
          {
            BoxCollider2D* aabb = dynamic_cast<BoxCollider2D*>(*iterator2);
            
            if(TestCCVsBC(*circle, *aabb))
              std::cout << "Circle (" << circle->_id << ") collided with AABB ("<< aabb->_id <<")." <<std::endl;
          }
          else if((*iterator2)->_type == CIRCLE_COLLIDER)
          {
            CircleCollider2D* circle2 = dynamic_cast<CircleCollider2D*>(*iterator2);
            
            if(circle->TestCCvsCC(*circle2))
              std::cout << "Circle (" << circle->_id << ") collided with Circle ("<< circle2->_id <<")." <<std::endl;
            
          }
        }
        
        iterator2++;
      }
      
      iterator++;
		}
    
    std::cout << "~~~~~~~~~~~~~~~~~~" <<std::endl;
  }
  
  void CreateCircleCollider(const Vector3& _v, const float& r)
  {
    CircleCollider2D* newCircle = new CircleCollider2D{_v, r};
    newCircle->_id = _count;
    newCircle->_type = CIRCLE_COLLIDER;
    
    _ListCollider2D.push_back(dynamic_cast<Collider2D*>(newCircle));
    
    _count++;
  }
  
  void CreateBoxCollider(const Vector3& _mMinPos, const Vector3& _mMaxPos)
  {
    BoxCollider2D* newBox = new BoxCollider2D{_mMinPos, _mMaxPos};
    newBox->_id = _count;
    newBox->_type = BOX_COLLIDER;
    
    _ListCollider2D.push_back(dynamic_cast<Collider2D*>(newBox));
    
    _count++;
  }
  
  
};

#endif