import greenfoot.*;  // (World, Actor, GreenfootImage, Greenfoot and MouseInfo)

/**
 * Write a description of class Critter here.
 * 
 * Bryce Bauer
 * 11/29/11
 */
public class Critter extends Actor
{
    private static final int EAST = 0;
    private static final int WEST = 1;
    private static final int NORTH = 2;
    private static final int SOUTH = 3;
    public int direction;
    /**
     * Turns towards the left.
     */
    public void turnLeft()
    {
        switch(direction) 
        {
            case SOUTH :
                setDirection(EAST);
                break;
            case EAST :
                setDirection(NORTH);
                break;
            case NORTH :
                setDirection(WEST);
                break;
            case WEST :
                setDirection(SOUTH);
                break;
        }
    }
    
        public void setDirection(int direction)
    {
        this.direction = direction;
        switch(direction) {
            case SOUTH :
                setRotation(90);
                break;
            case EAST :
                setRotation(0);
                break;
            case NORTH :
                setRotation(270);
                break;
            case WEST :
                setRotation(180);
                break;
            default :
                break;
        }
    }

    /**
     * Turns towards the right.
     */
    public void turnRight()
    {
        switch(direction) 
        {
            case SOUTH :
                setDirection(WEST);
                break;
            case EAST :
                setDirection(SOUTH);
                break;
            case NORTH :
                setDirection(EAST);
                break;
            case WEST :
                setDirection(NORTH);
                break;
        }
    }
    
         /**
     * Test if we can move forward. Return true if we can, false otherwise.
     */
    public boolean canMove()
    {
        World myWorld = getWorld();
        int x = getX();
        int y = getY();
        switch(direction) {
            case SOUTH :
                y++;
                break;
            case EAST :
                x++;
                break;
            case NORTH :
                y--;
                break;
            case WEST :
                x--;
                break;
        }
        // test for outside border
        if (x >= myWorld.getWidth() || y >= myWorld.getHeight()) {
            return false;
        }
        else if (x < 0 || y < 0) {
            return false;
        }
        return true;
    }
     
      /**
     * Move one cell forward in the current direction.
     */
    public void move()
    {
        if (!canMove()) {
            return;
        }
        double rand = Math.random();
        switch(direction) {
            case SOUTH :
                
                if (rand < .8)
                   setLocation(getX(), getY() + 1);
                else if (rand < .95)
                   setLocation(getX() + 1, getY());
                else
                   setLocation(getX() - 1, getY());
                break;
            case EAST :
                if (rand < .8)
                 setLocation(getX() + 1, getY());
                else if (rand < .95)
                 setLocation(getX(), getY() - 1);
                else
                setLocation(getX(), getY() + 1);
                break;
            case NORTH :
                if (rand < .8)
                 setLocation(getX(), getY() - 1);
                else if (rand < .95)
                 setLocation(getX() - 1, getY());
                else
                 setLocation(getX() + 1, getY());
                break;
            case WEST :
                 if (rand < .8)
                setLocation(getX() - 1, getY());
                else if (rand < .95)
                setLocation(getX(), getY() + 1);
                else
                setLocation(getX(), getY() - 1);
                break;
        }
    }
}
