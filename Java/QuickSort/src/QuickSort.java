public class QuickSort {
    public static <Patient extends Comparable<Patient>> void sort(Patient[] patientListCopy){
        quickSort(patientListCopy, 0, patientListCopy.length - 1);
    }
    private static <Patient extends Comparable<Patient>> void quickSort(Patient[] patientListCopy, int first, int last){
        if (first < last){
            int pivIndex = partition(patientListCopy, first, last);
            quickSort(patientListCopy, first, pivIndex - 1);
            quickSort(patientListCopy, pivIndex + 1, last);
        }
    }
    private static <Patient extends Comparable<Patient>> int partition(Patient[] patientListCopy, int first, int last){
        Patient pivot = patientListCopy[first];
        int up = first;
        int down = last;
       
        do {
            while ((up < last) && (pivot.compareTo(patientListCopy[up]) >=0)){
                up++;
            }
            while (pivot.compareTo(patientListCopy[down]) < 0){
                down--;
            }
            if (up < down){
                swap(patientListCopy, up, down);
            }
        } while (up < down);
        swap(patientListCopy, up, down);
        return down;
    }
   
    private static <Patient extends Comparable<Patient>> void swap(Patient[] patientListCopy, int up, int down){
        Patient temp;
        temp = patientListCopy[up];
        patientListCopy[up] = patientListCopy[down];
        patientListCopy[down] = temp;
    }
}
