import greenfoot.*;  // (World, Actor, GreenfootImage, and Greenfoot)

import java.util.List;
import java.util.ArrayList;

/**
 * Seahorse. A Seahorse moves forward until it can't do so anymore, at
 * which point it turns right. If a seahorse finds a pizza, it eats it.
 * 
 * Bryce Bauer
 * 11/26/11
 */
public class Seahorse extends Critter
{
    private static final int EAST = 0;
    private static final int WEST = 1;
    private static final int NORTH = 2;
    private static final int SOUTH = 3;

    private int direction;
    private int pizzaEaten;

    public Seahorse()
    {
        setDirection(SOUTH);
        pizzaEaten = 0;
    }

    /**
     * Do whatever the Seahorse likes to to just now.
     */
    public void act()
    {
      if(foundPizza()) {
          eatPizza();
          turnLeft();
       }
      else if(canMove()) {
          move();
        }
      else
      {
          turnRight();

       }
    }

         /**
     * Sets the direction we're facing.
     */
   

    /**
     * Check whether there is a pizza in the same cell as we are.
     */
    public boolean foundPizza()
    {
        Actor Pizza = getOneObjectAtOffset(0, 0, Pizza.class);
        if(Pizza != null) {
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * Eat a Pizza.
     */
    public void eatPizza()
    {
        Actor Pizza = getOneObjectAtOffset(0, 0, Pizza.class);
        if(Pizza != null) {
            // eat the pizza...
            getWorld().removeObject(Pizza);
            pizzaEaten = pizzaEaten + 1; 
        }
       
    }
 
     /**
     * Move one cell forward in the current direction.
     */
    


    /**
     * Tell how many leaves we have eaten.
     */
    public int getPizzaEaten()
    {
        return pizzaEaten;
    }
}
    
      