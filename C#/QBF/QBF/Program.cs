using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;


namespace QBF
{
    class Program
    {
       // static Semaphore threadPool;
        static Mutex mut = new Mutex();
        static Thread firstThread;
        static Thread secondThread;
        static int length;
        static char[] textArray;
        static Boolean locked = false;
        static Boolean doubLocked = false;
        
        static void Main(string[] args)
        {
            
            StreamReader reader = File.OpenText("C:/Users/bwbba_000/Desktop/QBFD.txt");
            string contents = reader.ReadToEnd();
            textArray = new char[contents.Length];
            length = contents.Length;
            int i = 0;
            for (; i < length; i++)
            {
                textArray[i] = contents[i];
                //Console.Write(textArray[i]);
            } 
         //   threadPool = new Semaphore(0, 3);
            firstThread = new Thread(new ThreadStart(printIT));
            secondThread = new Thread(new ThreadStart(printIT));

            //Console.Write("working");

            firstThread.Start();
            //Console.Write("working");
            secondThread.Start();
            //Console.Write("working");
           // threadPool.Release(3);
            
            Console.ReadLine();
        }

        static void printIT()
        {
           /* while (locked == true)
            {
                while (doubLocked == true)
                {

                }
                doubLocked = false;
            }
            locked = true;
            doubLocked = true;*/
            //Console.Write("here");

            int j = 0;
            if (mut.WaitOne(1000))
            {
                Thread.Sleep(5000);
                for (; j < length; j++)
                {
                    Console.Write(textArray[j]);
                    locked = false;
                }
                mut.ReleaseMutex();
            }
            
            
        }
    }

}
