//
//  WorldPosition.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__WorldPosition__
#define __TowerDefense__WorldPosition__

#define SCREEN_X 1024
#define SCREEN_Y 728

class WorldPosition
{
public:
    /// \brief change the value of the taken parameters from the world position to the screen one
    static void worldToScreenPosition(float& x, float& y);

    /// \brief change the value of the taken parameters from the world position to the screen one
    static void screenToWorldPosition(float& x, float& y);
};

#endif