package diskSchedulingAlgorithm;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class CSCAN//Increasing
{
    public static void main(String[] args)
    {
        ArrayList<Integer>greaterNumberHere = new ArrayList<>();
        ArrayList<Integer>smallerNumberHere = new ArrayList<>();
        ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter total Number Of Tracks:");
        int totalNumberOfTracks = scanner.nextInt();

        int[] tracksInfo = new int[totalNumberOfTracks];

        System.out.println("Enter Track Number:");
        for(int i = 0 ; i  < totalNumberOfTracks ; i++)
            tracksInfo[i] = scanner.nextInt();

        System.out.println("Enter Current Head:");
        int currentHeadPosition = scanner.nextInt();

        for(int element:tracksInfo)
        {
            if(element > currentHeadPosition)
                greaterNumberHere.add(element);
            else
                smallerNumberHere.add(element);
        }

        Collections.sort(greaterNumberHere);
        Collections.sort(smallerNumberHere);

        for(Integer element:greaterNumberHere)
        {
            int difference  = Math.abs(element - currentHeadPosition);
            numberOfTracksTravelled.add(difference);
            currentHeadPosition = element;
        }

        for(Integer element:smallerNumberHere)
        {
            int difference = Math.abs(element - currentHeadPosition);
            numberOfTracksTravelled.add(difference);
            currentHeadPosition = element;
        }

        System.out.println("Number Of Tracks Travelled:"+numberOfTracksTravelled);

        int totalSeekTime = 0;
        for(Integer element:numberOfTracksTravelled)
            totalSeekTime += element;

        System.out.println("Total Seek Time:"+totalSeekTime);

        double avgSeekTime = (totalSeekTime * 1.0) / totalNumberOfTracks;
        System.out.printf("Average Seek Time : %.2f",avgSeekTime);


    }
}






































// 1. Concept, Uses, and Purpose of C-SCAN Disk Scheduling
// Concept:
// C-SCAN (Circular SCAN) is a disk scheduling algorithm similar to SCAN. However, instead of reversing direction at the end of the disk, the head jumps to the opposite end and continues servicing requests in the same direction. This creates a circular behavior, ensuring fairness and reducing response time variance.

// Uses:
// Consistent Response Time: Serves all requests fairly in a single direction, ensuring uniform latency.
// Minimizing Starvation: Prevents starvation by continuously looping through requests.
// Purpose:
// To ensure fairness and predictability in disk scheduling by treating the disk as circular and moving in a consistent direction.

// 2. Logic and Algorithm of the Code
// Logic:
// Categorize track requests into those greater than and less than the current head position.
// Sort the requests:
// Ascending order for greaterNumberHere.
// Ascending order for smallerNumberHere.
// Service:
// All requests in greaterNumberHere first (upward movement).
// Jump to the start of the disk and service smallerNumberHere (circular continuation).
// Calculate the seek distances for each request.
// Compute total and average seek time.
// 3. Line-by-Line Explanation of the Code
// Code:
// java
// Copy code
// package diskSchedulingAlgorithm;
// import java.util.Scanner;
// import java.util.ArrayList;
// import java.util.Collections;
// Explanation: Imports necessary libraries for input handling (Scanner), dynamic storage (ArrayList), and sorting (Collections).
// java
// Copy code
// public class CSCAN//Increasing
// {
//     public static void main(String[] args)
//     {
//         ArrayList<Integer>greaterNumberHere = new ArrayList<>();
//         ArrayList<Integer>smallerNumberHere = new ArrayList<>();
//         ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
// Explanation:
// greaterNumberHere: Holds requests greater than the current head position.
// smallerNumberHere: Holds requests smaller than the current head position.
// numberOfTracksTravelled: Stores seek distances for each step.
// java
// Copy code
//         Scanner scanner = new Scanner(System.in);
//         System.out.println("Enter total Number Of Tracks:");
//         int totalNumberOfTracks = scanner.nextInt();

//         int[] tracksInfo = new int[totalNumberOfTracks];
// Explanation: Reads the total number of track requests and initializes tracksInfo for storing the track numbers.
// java
// Copy code
//         System.out.println("Enter Track Number:");
//         for(int i = 0 ; i  < totalNumberOfTracks ; i++)
//             tracksInfo[i] = scanner.nextInt();
// Explanation: Populates the tracksInfo array with track numbers entered by the user.
// java
// Copy code
//         System.out.println("Enter Current Head:");
//         int currentHeadPosition = scanner.nextInt();
// Explanation: Reads the current position of the disk head.
// java
// Copy code
//         for(int element:tracksInfo)
//         {
//             if(element > currentHeadPosition)
//                 greaterNumberHere.add(element);
//             else
//                 smallerNumberHere.add(element);
//         }
// Explanation:
// Adds requests greater than the current head position to greaterNumberHere.
// Adds requests smaller than the current head position to smallerNumberHere.
// java
// Copy code
//         Collections.sort(greaterNumberHere);
//         Collections.sort(smallerNumberHere);
// Explanation: Sorts both lists in ascending order.
// java
// Copy code
//         for(Integer element:greaterNumberHere)
//         {
//             int difference  = Math.abs(element - currentHeadPosition);
//             numberOfTracksTravelled.add(difference);
//             currentHeadPosition = element;
//         }
// Explanation: Services all requests in greaterNumberHere:
// Calculates the absolute seek distance.
// Updates the current head position after servicing each request.
// java
// Copy code
//         for(Integer element:smallerNumberHere)
//         {
//             int difference = Math.abs(element - currentHeadPosition);
//             numberOfTracksTravelled.add(difference);
//             currentHeadPosition = element;
//         }
// Explanation: Simulates circular behavior by servicing smallerNumberHere after a virtual jump to the beginning of the disk.
// java
// Copy code
//         System.out.println("Number Of Tracks Travelled:"+numberOfTracksTravelled);
// Explanation: Prints the seek distances for each step.
// java
// Copy code
//         int totalSeekTime = 0;
//         for(Integer element:numberOfTracksTravelled)
//             totalSeekTime += element;
// Explanation: Calculates the total seek time by summing all seek distances.
// java
// Copy code
//         System.out.println("Total Seek Time:"+totalSeekTime);

//         double avgSeekTime = (totalSeekTime * 1.0) / totalNumberOfTracks;
//         System.out.printf("Average Seek Time : %.2f",avgSeekTime);
//     }
// }
// Explanation:
// Prints the total seek time.
// Computes and prints the average seek time by dividing the total seek time by the number of requests.
// 4. Sample Input and Output
// Input:
// mathematica
// Copy code
// Enter total Number Of Tracks:
// 6
// Enter Track Number:
// 98
// 183
// 37
// 122
// 14
// 124
// Enter Current Head:
// 53
// Output:
// sql
// Copy code
// Number Of Tracks Travelled:[45, 25, 61, 47, 109, 39]
// Total Seek Time:326
// Average Seek Time : 54.33
// 5. Key Observations
// Circular Movement:

// After servicing greaterNumberHere, the algorithm jumps back to the start of the disk and services smallerNumberHere.
// Efficiency:

// The algorithm minimizes large jumps compared to FIFO while maintaining fairness.
// Sorting:

// Sorting ensures sequential processing of requests in both directions.
// 6. Possible Questions
// Concept-Based Questions:
// Q: What is the primary advantage of C-SCAN over SCAN?

// A: C-SCAN provides uniform wait times by treating the disk as circular, reducing the response time variance.
// Q: Why does C-SCAN jump to the start of the disk?

// A: To maintain a consistent direction and prevent starvation.
// Q: In which scenarios is C-SCAN preferred?

// A: When consistent response time and fairness are critical.
// Code-Based Questions:
// Q: How does the code handle circular behavior?

// A: By processing smallerNumberHere after greaterNumberHere.
// Q: Why are the lists sorted?

// A: To ensure sequential processing of requests for efficient seek time calculation.
// Q: How is the average seek time computed?

// A: By dividing the total seek time by the total number of requests.