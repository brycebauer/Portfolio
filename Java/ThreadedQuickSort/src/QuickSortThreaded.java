/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Bryce Bauer
 */
public class QuickSortThreaded extends Thread{
    int[] listOfIntegers;
    int lowIndex;
    int highIndex;
    int threadNumber;
    QuickSort QuickSort = new QuickSort();
    
   public QuickSortThreaded(int[] listOfIntegers, int lowIndex, int highIndex, int threadNumber){
       this.listOfIntegers = listOfIntegers;
       this.lowIndex = lowIndex;
       this.highIndex = highIndex;
       this.threadNumber = threadNumber;
   }
    
   @Override
   public void run(){
       long startTime = System.currentTimeMillis();
    int index = QuickSort.quickSort(listOfIntegers, lowIndex, highIndex, threadNumber); 
     System.out.print("the time for the sort is " + (System.currentTimeMillis() - startTime) + " ms");
   }
    
}
