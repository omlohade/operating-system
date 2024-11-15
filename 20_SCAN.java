package diskSchedulingAlgorithm;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class SCAN//Increasing
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

        for(int i = 0 ; i < smallerNumberHere.size() / 2 ;i++)
        {
            Integer element = smallerNumberHere.get(i);
            smallerNumberHere.set(i, smallerNumberHere.get(smallerNumberHere.size() - i -1));
            smallerNumberHere.set(smallerNumberHere.size() - i - 1,element);
        }

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





































// 1. Concept, Uses, and Purpose of SCAN Disk Scheduling
// Concept:
// The SCAN algorithm moves the disk head in one direction, servicing all requests until it reaches the end of the disk. After reaching the end, it reverses direction and services requests on the way back. This bi-directional movement mimics an elevator, ensuring no request is ignored.

// Uses:
// Fair Scheduling: Ensures all requests are serviced within a reasonable time.
// Efficient Seek Time: Reduces the seek time compared to algorithms like FIFO.
// Why Use It:
// SCAN is beneficial in scenarios where fairness and predictability are critical. It balances seek time and reduces starvation compared to SSTF by moving continuously in both directions.

// 2. Logic and Algorithm of the Code
// Logic:
// The program implements SCAN by:

// Dividing requests into two categories: greater and smaller than the current head position.
// Sorting these categories to service requests in ascending order on the way up and descending order on the way down.
// Calculating seek distances for each serviced track.
// Computing the total and average seek time.
// Algorithm:
// Input the total number of track requests, track numbers, and the current head position.
// Categorize requests into:
// greaterNumberHere: Tracks greater than the current head position.
// smallerNumberHere: Tracks less than the current head position.
// Sort the requests:
// Ascending for greaterNumberHere.
// Descending for smallerNumberHere.
// Process all tracks in greaterNumberHere first (upwards movement).
// Process all tracks in smallerNumberHere (downwards movement).
// Compute the total seek time and average seek time.
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
// public class SCAN //Increasing
// {
//     public static void main(String[] args)
//     {
//         ArrayList<Integer>greaterNumberHere = new ArrayList<>();
//         ArrayList<Integer>smallerNumberHere = new ArrayList<>();
//         ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
// Explanation: Initializes:
// greaterNumberHere: Tracks greater than the current head position.
// smallerNumberHere: Tracks less than the current head position.
// numberOfTracksTravelled: Seek distances for each step.
// java
// Copy code
//         Scanner scanner = new Scanner(System.in);
//         System.out.println("Enter total Number Of Tracks:");
//         int totalNumberOfTracks = scanner.nextInt();

//         int[] tracksInfo = new int[totalNumberOfTracks];
// Explanation: Reads the total number of tracks and initializes tracksInfo to store track numbers.
// java
// Copy code
//         System.out.println("Enter Track Number:");
//         for(int i = 0 ; i  < totalNumberOfTracks ; i++)
//             tracksInfo[i] = scanner.nextInt();
// Explanation: Populates tracksInfo with user input.
// java
// Copy code
//         System.out.println("Enter Current Head:");
//         int currentHeadPosition = scanner.nextInt();
// Explanation: Reads the initial position of the disk head.
// java
// Copy code
//         for(int element:tracksInfo)
//         {
//             if(element > currentHeadPosition)
//                 greaterNumberHere.add(element);
//             else
//                 smallerNumberHere.add(element);
//         }
// Explanation: Categorizes requests into:
// greaterNumberHere: Tracks greater than the head position.
// smallerNumberHere: Tracks less than the head position.
// java
// Copy code
//         Collections.sort(greaterNumberHere);
//         Collections.sort(smallerNumberHere);
// Explanation: Sorts the requests:
// Ascending for greaterNumberHere for upward movement.
// Ascending for smallerNumberHere, which will later be reversed for downward movement.
// java
// Copy code
//         for(int i = 0 ; i < smallerNumberHere.size() / 2 ;i++)
//         {
//             Integer element = smallerNumberHere.get(i);
//             smallerNumberHere.set(i, smallerNumberHere.get(smallerNumberHere.size() - i -1));
//             smallerNumberHere.set(smallerNumberHere.size() - i - 1,element);
//         }
// Explanation: Reverses smallerNumberHere to process requests in descending order during downward movement.
// java
// Copy code
//         for(Integer element:greaterNumberHere)
//         {
//             int difference  = Math.abs(element - currentHeadPosition);
//             numberOfTracksTravelled.add(difference);
//             currentHeadPosition = element;
//         }
// Explanation: Processes all requests in greaterNumberHere:
// Computes the absolute difference between the current head position and each request.
// Updates the head position after servicing each request.
// java
// Copy code
//         for(Integer element:smallerNumberHere)
//         {
//             int difference = Math.abs(element - currentHeadPosition);
//             numberOfTracksTravelled.add(difference);
//             currentHeadPosition = element;
//         }
// Explanation: Processes all requests in smallerNumberHere similarly, simulating the downward movement.
// java
// Copy code
//         System.out.println("Number Of Tracks Travelled:"+numberOfTracksTravelled);
// Explanation: Prints the list of seek distances for each step.
// java
// Copy code
//         int totalSeekTime = 0;
//         for(Integer element:numberOfTracksTravelled)
//             totalSeekTime += element;
// Explanation: Calculates the total seek time by summing up all seek distances.
// java
// Copy code
//         System.out.println("Total Seek Time:"+totalSeekTime);

//         double avgSeekTime = (totalSeekTime * 1.0) / totalNumberOfTracks;
//         System.out.printf("Average Seek Time : %.2f",avgSeekTime);
//     }
// }
// Explanation: Computes and prints:
// Total seek time.
// Average seek time by dividing the total seek time by the number of tracks.
// 4. Sample Input and Output
// Input:
// mathematica
// Copy code
// Enter total Number Of Tracks:
// 5
// Enter Track Number:
// 98
// 183
// 37
// 122
// 14
// Enter Current Head:
// 50
// Output:
// sql
// Copy code
// Number Of Tracks Travelled:[48, 25, 24, 45, 123]
// Total Seek Time:265
// Average Seek Time : 53.00
// 5. Possible Questions and Answers
// Concept-Based Questions:
// Q: What is the SCAN disk scheduling algorithm?

// A: SCAN moves the disk head in one direction, servicing all requests until it reaches the end, then reverses direction to service remaining requests.
// Q: How does SCAN differ from SSTF?

// A: SCAN moves bi-directionally, servicing all requests along its path, while SSTF always services the closest request, irrespective of direction.
// Q: What are the advantages of SCAN?

// A: Reduces starvation and ensures fairness by servicing all requests along its path.
// Code-Based Questions:
// Q: Why is smallerNumberHere reversed in the code?

// A: To simulate downward movement by processing requests in descending order.
// Q: What happens if all requests are greater than the current head position?

// A: The smallerNumberHere list remains empty, and only greaterNumberHere is processed.
// Q: How is the total seek time calculated?

// A: By summing up all seek distances stored in numberOfTracksTravelled.
// Q: Why is sorting necessary in SCAN?

// A: Sorting ensures that requests are serviced sequentially, minimizing head movement.
