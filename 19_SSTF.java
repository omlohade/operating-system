package diskSchedulingAlgorithm;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class SSTF //Increasing
{
    public static void main(String[] args)
    {
        int indexForGreaterNumberHere, indexForSmallerNumber;
        indexForGreaterNumberHere = indexForSmallerNumber = 0;
        ArrayList<Integer>greaterNumberHere = new ArrayList<>();
        ArrayList<Integer>smallerNumberHere = new ArrayList<>();
        ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();

        Scanner scanner = new Scanner(System.in);
        System.out.println("Total Number Of Tracks:");
        int totalNumberOfTracks = scanner.nextInt();
        int[] tracksInfo = new int[totalNumberOfTracks];

        System.out.println("Enter Track Number:");
        for(int i = 0 ; i  < totalNumberOfTracks ; i++)
            tracksInfo[i] = scanner.nextInt();

        System.out.println("Enter Current Head:");
        int currentHeadPosition = scanner.nextInt();

        for(int element:tracksInfo)
        {
            if(element<currentHeadPosition)
                smallerNumberHere.add(element);
            else
                greaterNumberHere.add(element);
        }

        Collections.sort(greaterNumberHere);
        Collections.sort(smallerNumberHere);
        for(int i = 0; i < smallerNumberHere.size() / 2 ; i++)
        {
            Integer element = smallerNumberHere.get(i);
            smallerNumberHere.set(i,smallerNumberHere.get(smallerNumberHere.size() - i - 1));
            smallerNumberHere.set(smallerNumberHere.size() - i - 1,element);
        }
        System.out.println("Greater Number Here:"+greaterNumberHere);
        System.out.println("Smaller Number Here:"+smallerNumberHere);
        while(indexForSmallerNumber!= smallerNumberHere.size() && indexForGreaterNumberHere !=greaterNumberHere.size())
        {
            //Check for smaller difference
            int difference1 = Math.abs(smallerNumberHere.get(indexForSmallerNumber) - currentHeadPosition);
            int difference2 = Math.abs(greaterNumberHere.get(indexForGreaterNumberHere) - currentHeadPosition);
            if(difference1 >= difference2)
            {
                numberOfTracksTravelled.add(difference2);
                currentHeadPosition = greaterNumberHere.get(indexForGreaterNumberHere);
                indexForGreaterNumberHere++;
            }
            else
            {
                numberOfTracksTravelled.add(difference1);
                currentHeadPosition = smallerNumberHere.get(indexForSmallerNumber);
                indexForSmallerNumber++;
            }
        }

        if(indexForSmallerNumber == smallerNumberHere.size())
        {
            //Element of greaterNumberHere are remaining
            do
            {
                int difference = Math.abs(greaterNumberHere.get(indexForGreaterNumberHere) - currentHeadPosition);
                numberOfTracksTravelled.add(difference);
                currentHeadPosition = greaterNumberHere.get(indexForGreaterNumberHere);
                indexForGreaterNumberHere++;
            }while(indexForGreaterNumberHere != greaterNumberHere.size());
        }
        else
        {
            //Element of smallerNumberHere are remaining
            do
            {
                int difference = Math.abs(smallerNumberHere.get(indexForSmallerNumber) - currentHeadPosition);
                numberOfTracksTravelled.add(difference);
                currentHeadPosition = smallerNumberHere.get(indexForSmallerNumber);
                indexForSmallerNumber++;
            }while(indexForSmallerNumber != smallerNumberHere.size());
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








































// 1. Concept, Uses, and Purpose of SSTF Disk Scheduling
// Concept:
// SSTF (Shortest Seek Time First) is a disk scheduling algorithm that selects the request closest to the current head position, minimizing the seek time for each step. It prioritizes requests based on proximity, reducing the total seek time compared to FIFO.

// Uses:
// Minimizes Seek Time: Effective in reducing disk head movement and total seek time.
// Improves Performance: Commonly used in systems where performance is critical.
// Why Use It:
// Unlike FIFO, SSTF considers the position of requests relative to the current head position, ensuring the next request serviced is the nearest. However, it can lead to starvation if requests further away are perpetually ignored.

// 2. Logic and Algorithm of the Code
// Logic:
// The program implements SSTF by:

// Dividing track requests into two categories: greater than and less than the current head position.
// Sorting these categories to process requests in the order of proximity.
// Iteratively selecting the nearest track to the current head position.
// Calculating the total and average seek time.
// Algorithm:
// Input the total number of track requests, track numbers, and the current head position.
// Categorize requests into two lists:
// smallerNumberHere: Tracks less than the head position.
// greaterNumberHere: Tracks greater than or equal to the head position.
// Sort both lists.
// Reverse the smallerNumberHere list to prioritize tracks closest to the head position.
// While there are unprocessed requests in both lists:
// Compare the nearest elements from both lists to the current head position.
// Select the track with the smaller distance.
// Process the remaining requests in either list if the other becomes empty.
// Compute the total seek time as the sum of all distances.
// Calculate the average seek time.
// 3. Line-by-Line Explanation of the Code
// Code:
// java
// Copy code
// package diskSchedulingAlgorithm;
// import java.util.Scanner;
// import java.util.ArrayList;
// import java.util.Collections;
// Explanation: Declares the package and imports necessary libraries for input (Scanner), dynamic data storage (ArrayList), and sorting (Collections).
// java
// Copy code
// public class SSTF //Increasing
// {
//     public static void main(String[] args)
//     {
//         int indexForGreaterNumberHere, indexForSmallerNumber;
//         indexForGreaterNumberHere = indexForSmallerNumber = 0;
// Explanation: Initializes indices for tracking processed elements in the sorted greaterNumberHere and smallerNumberHere lists.
// java
// Copy code
//         ArrayList<Integer>greaterNumberHere = new ArrayList<>();
//         ArrayList<Integer>smallerNumberHere = new ArrayList<>();
//         ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
// Explanation: Declares lists to store:
// greaterNumberHere: Tracks greater than or equal to the head position.
// smallerNumberHere: Tracks less than the head position.
// numberOfTracksTravelled: Seek distances for each step.
// java
// Copy code
//         Scanner scanner = new Scanner(System.in);
//         System.out.println("Total Number Of Tracks:");
//         int totalNumberOfTracks = scanner.nextInt();
//         int[] tracksInfo = new int[totalNumberOfTracks];
// Explanation: Reads the total number of tracks and initializes tracksInfo to store the track numbers.
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
//             if(element<currentHeadPosition)
//                 smallerNumberHere.add(element);
//             else
//                 greaterNumberHere.add(element);
//         }
// Explanation: Categorizes track requests into smallerNumberHere and greaterNumberHere based on their relationship to the current head position.
// java
// Copy code
//         Collections.sort(greaterNumberHere);
//         Collections.sort(smallerNumberHere);
//         for(int i = 0; i < smallerNumberHere.size() / 2 ; i++)
//         {
//             Integer element = smallerNumberHere.get(i);
//             smallerNumberHere.set(i,smallerNumberHere.get(smallerNumberHere.size() - i - 1));
//             smallerNumberHere.set(smallerNumberHere.size() - i - 1,element);
//         }
// Explanation:
// Sorts both lists to enable efficient processing.
// Reverses smallerNumberHere to process requests in decreasing order of proximity.
// java
// Copy code
//         while(indexForSmallerNumber!= smallerNumberHere.size() && indexForGreaterNumberHere !=greaterNumberHere.size())
//         {
//             int difference1 = Math.abs(smallerNumberHere.get(indexForSmallerNumber) - currentHeadPosition);
//             int difference2 = Math.abs(greaterNumberHere.get(indexForGreaterNumberHere) - currentHeadPosition);
//             if(difference1 >= difference2)
//             {
//                 numberOfTracksTravelled.add(difference2);
//                 currentHeadPosition = greaterNumberHere.get(indexForGreaterNumberHere);
//                 indexForGreaterNumberHere++;
//             }
//             else
//             {
//                 numberOfTracksTravelled.add(difference1);
//                 currentHeadPosition = smallerNumberHere.get(indexForSmallerNumber);
//                 indexForSmallerNumber++;
//             }
//         }
// Explanation: Processes requests iteratively:
// Compares the nearest elements from both lists.
// Chooses the closest track to minimize seek time.
// Updates the currentHeadPosition and indices accordingly.
// java
// Copy code
//         if(indexForSmallerNumber == smallerNumberHere.size())
//         {
//             do
//             {
//                 int difference = Math.abs(greaterNumberHere.get(indexForGreaterNumberHere) - currentHeadPosition);
//                 numberOfTracksTravelled.add(difference);
//                 currentHeadPosition = greaterNumberHere.get(indexForGreaterNumberHere);
//                 indexForGreaterNumberHere++;
//             }while(indexForGreaterNumberHere != greaterNumberHere.size());
//         }
// Explanation: Handles remaining elements in greaterNumberHere when smallerNumberHere is exhausted.
// java
// Copy code
//         else
//         {
//             do
//             {
//                 int difference = Math.abs(smallerNumberHere.get(indexForSmallerNumber) - currentHeadPosition);
//                 numberOfTracksTravelled.add(difference);
//                 currentHeadPosition = smallerNumberHere.get(indexForSmallerNumber);
//                 indexForSmallerNumber++;
//             }while(indexForSmallerNumber != smallerNumberHere.size());
//         }
// Explanation: Handles remaining elements in smallerNumberHere when greaterNumberHere is exhausted.
// java
// Copy code
//         System.out.println("Number Of Tracks Travelled:"+numberOfTracksTravelled);
// Explanation: Prints the seek distances for each step.
// java
// Copy code
//         int totalSeekTime = 0;
//         for(Integer element:numberOfTracksTravelled)
//             totalSeekTime += element;
// Explanation: Computes the total seek time as the sum of all distances.
// java
// Copy code
//         System.out.println("Total Seek Time:"+totalSeekTime);

//         double avgSeekTime = (totalSeekTime * 1.0) / totalNumberOfTracks;
//         System.out.printf("Average Seek Time : %.2f",avgSeekTime);
//     }
// }
// Explanation: Calculates and prints the total and average seek times.
// 4. Possible Questions and Answers
// Concept-Based Questions:
// Q: What is SSTF disk scheduling?

// A: SSTF selects the request closest to the current head position, reducing seek time.
// Q: What are the advantages of SSTF?

// A: Minimizes seek time and improves efficiency compared to FIFO.
// Q: What is a disadvantage of SSTF?

// A: It can lead to starvation, where distant requests are ignored for long periods.
// Q: Why do we sort track requests in SSTF?

// A: Sorting ensures that requests are processed in the order of proximity.
// Code-Based Questions:
// Q: Why is Math.abs used in the code?

// A: To compute the absolute difference between the head position and a track.
// Q: Why is the smallerNumberHere list reversed?

// A: To process tracks closer to the head position first in descending order.
// Q: What happens if one list is exhausted during processing?

// A: The remaining requests in the other list are processed sequentially.
// Q: How is the average seek time calculated?

// A: By dividing the total seek time by the number of track requests.
// This detailed breakdown should provide all the necessary information for your lab exam preparation!