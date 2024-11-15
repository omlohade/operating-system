package diskSchedulingAlgorithm;
import java.util.Scanner;
import java.util.ArrayList;

public class FIFO
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
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
            numberOfTracksTravelled.add(Math.abs(currentHeadPosition - element));
            currentHeadPosition = element;
        }

        System.out.println("Number of Tracks Travelled each time:"+numberOfTracksTravelled);
        int totalSeekTime = 0;
        for(Integer element:numberOfTracksTravelled)
            totalSeekTime += element;
        System.out.println("Total Seek Time:"+totalSeekTime);

        double avgSeekTime = ((totalSeekTime * 1.0)/totalNumberOfTracks);
        System.out.printf("Average Seek Time:%.2f",avgSeekTime);
    }
}



























// 1. Concept, Uses, and Purpose of FIFO Disk Scheduling
// Concept:
// FIFO disk scheduling is one of the simplest disk scheduling algorithms. The requests for disk access are processed in the order they arrive. The disk head services each request sequentially, without reordering, resulting in predictable behavior but not necessarily optimal seek time.

// Uses:
// Predictable Behavior: Useful in systems where simplicity and predictability are more critical than optimal performance.
// Batch Systems: Ensures fairness by servicing requests in arrival order.
// Why Use It:
// FIFO is simple to implement and guarantees that requests are handled in the order they arrive. However, it may lead to higher seek time if the requests are scattered across the disk, as it doesn't account for minimizing head movement.

// 2. Logic and Algorithm of the Code
// Logic:
// The program simulates the FIFO disk scheduling algorithm by:

// Taking the number of track requests, the track numbers, and the initial head position as input.
// Calculating the distance traveled by the disk head for each request.
// Summing up the distances to find the total seek time and calculating the average seek time.
// Algorithm:
// Input the total number of track requests, the track numbers, and the current head position.
// Initialize an empty list to store the number of tracks traveled for each request.
// For each track:
// Compute the absolute difference between the current head position and the requested track.
// Update the current head position to the requested track.
// Calculate the total seek time by summing the distances.
// Compute the average seek time as the total seek time divided by the number of requests.
// 3. Line-by-Line Explanation of the Code
// Code:
// java
// Copy code
// package diskSchedulingAlgorithm;
// import java.util.Scanner;
// import java.util.ArrayList;
// Explanation: Defines the package and imports the necessary libraries for user input (Scanner) and storing results (ArrayList).
// java
// Copy code
// public class FIFO
// {
//     public static void main(String[] args)
//     {
//         Scanner scanner = new Scanner(System.in);
//         ArrayList<Integer>numberOfTracksTravelled = new ArrayList<>();
// Explanation: Defines the FIFO class. Inside the main method, initializes a Scanner object for input and an ArrayList to store the number of tracks traveled.
// java
// Copy code
//         System.out.println("Total Number Of Tracks:");
//         int totalNumberOfTracks = scanner.nextInt();
//         int[] tracksInfo = new int[totalNumberOfTracks];
// Explanation: Prompts the user to enter the total number of track requests. Stores the input in totalNumberOfTracks and initializes an array tracksInfo to hold the track numbers.
// java
// Copy code
//         System.out.println("Enter Track Number:");
//         for(int i = 0 ; i  < totalNumberOfTracks ; i++)
//             tracksInfo[i] = scanner.nextInt();
// Explanation: Prompts the user to enter each track number, iteratively storing them in the tracksInfo array.
// java
// Copy code
//         System.out.println("Enter Current Head:");
//         int currentHeadPosition = scanner.nextInt();
// Explanation: Takes the initial position of the disk head from the user and stores it in currentHeadPosition.
// java
// Copy code
//         for(int element:tracksInfo)
//         {
//             numberOfTracksTravelled.add(Math.abs(currentHeadPosition - element));
//             currentHeadPosition = element;
//         }
// Explanation: Iterates through each track request in tracksInfo:
// Calculates the absolute distance between currentHeadPosition and the requested track.
// Updates currentHeadPosition to the current track.
// java
// Copy code
//         System.out.println("Number of Tracks Travelled each time:"+numberOfTracksTravelled);
// Explanation: Prints the list of distances (tracks traveled) for each request.
// java
// Copy code
//         int totalSeekTime = 0;
//         for(Integer element:numberOfTracksTravelled)
//             totalSeekTime += element;
// Explanation: Initializes totalSeekTime to 0. Iterates through numberOfTracksTravelled to compute the sum of distances.
// java
// Copy code
//         System.out.println("Total Seek Time:"+totalSeekTime);
// Explanation: Prints the total seek time.
// java
// Copy code
//         double avgSeekTime = ((totalSeekTime * 1.0)/totalNumberOfTracks);
//         System.out.printf("Average Seek Time:%.2f",avgSeekTime);
//     }
// }
// Explanation: Computes the average seek time by dividing the total seek time by the number of requests and prints it in formatted output.
// 4. Possible Questions and Answers
// Concept-Based Questions:
// Q: What is FIFO disk scheduling?

// A: FIFO disk scheduling processes disk requests in the order they arrive without reordering. It is simple but can result in suboptimal seek times if requests are scattered.
// Q: What are the drawbacks of FIFO disk scheduling?

// A: It may cause high seek time when requests are far apart on the disk, leading to inefficient head movement.
// Q: Why is FIFO considered fair?

// A: It processes requests in the order they arrive, ensuring no request is starved.
// Q: What is seek time, and why is it important?

// A: Seek time is the time taken for the disk head to move to the requested track. It is crucial as it directly impacts the performance of disk I/O operations.
// Code Logic and Implementation Questions:
// Q: Why do we use Math.abs in the code?

// A: To calculate the absolute distance traveled by the disk head, as the head can move in either direction.
// Q: What is the purpose of updating currentHeadPosition in the loop?

// A: To reflect the position of the disk head after servicing each request.
// Q: How is the average seek time calculated?

// A: By dividing the total seek time by the number of requests.
// Q: Why do we use an ArrayList to store distances traveled?

// A: To dynamically store and retrieve the distances for each request efficiently.
