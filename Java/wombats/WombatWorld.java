import greenfoot.*;  // imports Actor, World, Greenfoot, GreenfootImage

import java.util.Random;

/**
 * A world where wombats live.
 * 
 * Bryce Bauer
 * 11/29/11
 */
public class WombatWorld extends World
{
    /**
     * Create a new world with 8x8 cells and
     * with a cell size of 60x60 pixels
     */
    public WombatWorld() 
    {
        super(8, 11, 60);        
        setBackground("cell.jpg");
    }

    /**
     * Populate the world with a fixed scenario of wombats and leaves.
     */    
    public void populate()
    {
        Lemur a1 = new Lemur();
        addObject(a1, 4, 5);
        
        Wombat w1 = new Wombat();
        addObject(w1, 3, 3);
        
        Wombat w2 = new Wombat();
        addObject(w2, 1, 7);
        
        Wombat w3 = new Wombat();
        addObject(w3, 2, 9);
        
        Leaf l1 = new Leaf();
        addObject(l1, 5, 3);

        Leaf l2 = new Leaf();
        addObject(l2, 3, 1);

        Leaf l3 = new Leaf();
        addObject(l3, 7, 4);

        Leaf l4 = new Leaf();
        addObject(l4, 0, 5);

        Leaf l5 = new Leaf();
        addObject(l5, 5, 1);
        
        Leaf l6 = new Leaf();
        addObject(l6, 4, 7);
        
        Leaf l7 = new Leaf();  
        addObject(l7, 7, 9);
        
        Leaf l8 = new Leaf();
        addObject(l8, 2, 4);
        
        Leaf l9 = new Leaf();
        addObject(l9, 1, 5);
                
        Seahorse s1 = new Seahorse();
        addObject(s1, 6, 1);
                
        Seahorse s2 = new Seahorse();
        addObject(s2, 5, 6);
                
        Seahorse s3 = new Seahorse();
        addObject(s3, 3, 7);
        
        Pizza p1 = new Pizza();
        addObject(p1, 0, 3);
                
        Pizza p2 = new Pizza();
        addObject(p2, 7, 5);
                
        Pizza p3 = new Pizza();
        addObject(p3, 6, 5);
                
        Pizza p4 = new Pizza();
        addObject(p4, 0, 2);
        
        Pizza p5 = new Pizza();
        addObject(p5, 0, 9);
        
        Pizza p6 = new Pizza();
        addObject(p6, 3, 9);
        
        Pizza p7 = new Pizza();
        addObject(p7, 1, 6);
        
        Pizza p8 = new Pizza();
        addObject(p8, 1, 10);
        
        Pizza p9 = new Pizza();
        addObject(p9, 5, 10);
    }
    
    /**
     * Place a number of leaves into the world at random places.
     * The number of leaves can be specified.
     */
    public void randomLeaves(int howMany)
    {
        for(int i=0; i<howMany; i++) {
            Leaf leaf = new Leaf();
            int x = Greenfoot.getRandomNumber(getWidth());
            int y = Greenfoot.getRandomNumber(getHeight());
            addObject(leaf, x, y);
        }
    }
    /**
     * Place a number of pizza into the world at random places.
     * The number of pizza can be specified.
     */
    public void randomPizza(int howMany)
    {
        for(int i=0; i<howMany; i++) {
            Pizza Pizza = new Pizza();
            int x = Greenfoot.getRandomNumber(getWidth());
            int y = Greenfoot.getRandomNumber(getHeight());
            addObject(Pizza, x, y);
        }
    }
}