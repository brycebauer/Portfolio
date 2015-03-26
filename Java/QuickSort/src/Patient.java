public class Patient implements Comparable<Patient>{

 private int id, priority;
 Patient genericObject;

 public Patient(int idNumber, int priorityNumber){
 id = idNumber;
 priority = priorityNumber;
 }

 public int getId(){
 return id;
 }

 public int getPriority(){
 return priority;
 }
 
 @Override
 public int compareTo(Patient otherPatient){
 // The compareTo method must be implemented so that it returns a non-zero
 // positive integer if this object is larger than than the other object
 // (according to the instance variable against which they are being
 // compared), zero if they are equal, and a negative non-zero number if
 // this object is less than the other object. One way to do this is
 //
 if (this.id < otherPatient.id) {return -1;}
 else if (this.id > otherPatient.id) {return 1;}
 else return 0;
 //
 // However, a shorter way to accomplish the same thing for integer values is:
// return this.id - otherPatient.id;
 }
}
