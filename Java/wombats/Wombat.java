import greenfoot.*;  // (World, Actor, GreenfootImage, and Greenfoot)

import java.util.List;
import java.util.ArrayList;

/**
 * Wombat. A Wombat moves forward until it can't do so anymore, at
 * which point it turns left. If a wombat finds a leaf, it eats it.
 * 
 * Bryce Bauer
 * 11/29/11
 */
public class Wombat extends Critter
{
    private static final int EAST = 0;
    private static final int WEST = 1;
    private static final int NORTH = 2;
    private static final int SOUTH = 3;


    private int leavesEaten;

    public Wombat()
    {
        setDirection(EAST);
        leavesEaten = 0;
    }

    /**
     * Do whatever the wombat likes to to just now.
     */
    public void act()
    {
      if(foundLeaf()) {
          eatLeaf();
          turnRight();
       }
      else if(canMove()) {
          move();
        }
      else
      {
          eatSeahorse();
          turnLeft();
       }
    }

    /**
     * Check whether there is a leaf in the same cell as we are.
     */
    public boolean foundLeaf()
    {
        Actor leaf = getOneObjectAtOffset(0, 0, Leaf.class);
        if(leaf != null) {
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * Eat a leaf.
     */
    public void eatLeaf()
    {
        Actor leaf = getOneObjectAtOffset(0, 0, Leaf.class);
        if(leaf != null) {
            // eat the leaf...
            getWorld().removeObject(leaf);
            leavesEaten = leavesEaten + 1; 
        }
       
    }
    
    public void eatSeahorse()
    {
        if  (leavesEaten >= 3)
            {
        Actor Seahorse = getOneObjectAtOffset(0, 0, Seahorse.class);
        if(Seahorse != null) {
            // eat the Seahorse...
            getWorld().removeObject(Seahorse);

        }
    }
       
    }
     
    /**
     * Turns towards the left.
     */
   

    /**
     * Tell how many leaves we have eaten.
     */
    public int getLeavesEaten()
    {
        return leavesEaten;
    }
}