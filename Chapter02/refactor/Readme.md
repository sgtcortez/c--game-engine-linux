# Summary

- [Introduction](#Introduction)   
- [Improvement](#Improvement)
- [References](#References)

# Introduction

I have made this refactor, just because I dont like the author code ... It seems a lot complex and, does not follow a good object oriented design.     
For example, in the Actor.cpp file, there is this piece of code:  
```cpp   
Actor::~Actor()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}
```

The actor holds a reference to the **Game** object.  
So, when an actor goes out of scope(freed), it calls the game method to remove him ...   
Also, the Actor class has circular referece, the Game has N actors, and every actor has the game object.    

Also, in some parts of the code, the actor used `**container(vector,map)**.emplace_back()` method, which is used to construct the object to be inserted ...    
It just adds more complexity to the code. So I have changed it to use the **push_back** method.

I also, refactored the components part, in the author original code, every actor has components, and the Game Object also has components(?).   
In my refactored version, I have created 3 types of components: 

- KeyboardComponent   

    Which is called in the game input phase.   

- UpdatableComponent

    Which is called in the game update phase.

- DrawableComponent

    Which is called in the game draw(renderer) phase.    

Than, in the Actor.hpp there are 3 lists, which represents components of these 3 types.    
```cpp
class Actor
{
    protected:
        std::vector<KeyboardComponent  *> keyboard_components;
        std::vector<UpdatableComponent *> updatable_components;
        std::vector<DrawableComponent  *> drawables_components;   
...
}
```

Also in Actor.hpp, there are the definition of the 3 phases of the game:   
```c++
void input(const unsigned char* keyboard_state);
void update(const float delta_time);            
void draw(SDL_Renderer *renderer);
```



**Obs: The code is working as the same of the author code.**

# Improvement

Instead of using **raw pointers** I have refactored it to use C++11 **smart pointers**.  

So, an assumption that we have is that: **NO** new/malloc delete/free will be used.    
We are going to use only smart pointers to do the job 

# References

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)