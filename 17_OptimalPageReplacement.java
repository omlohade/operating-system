import java.util.*;

public class OptimalPageReplacement {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input the length of the reference string
        System.out.print("Enter the length of the reference string: ");
        int length = scanner.nextInt();

        // Input the reference string
        int[] referenceString = new int[length];
        System.out.println("Enter the reference string (space-separated): ");
        for (int i = 0; i < length; i++) {
            referenceString[i] = scanner.nextInt();
        }

        // Input the number of frames
        System.out.print("Enter the number of frames: ");
        int numOfFrames = scanner.nextInt();

        // Calculate page faults
        int pageFaults = calculatePageFaults(referenceString, numOfFrames);
        System.out.println("Number of Page Faults: " + pageFaults);
    }

    public static int calculatePageFaults(int[] referenceString, int numOfFrames) {
        Set<Integer> frames = new HashSet<>();
        int pageFaults = 0;

        for (int i = 0; i < referenceString.length; i++) {
            int page = referenceString[i];

            // If the page is not in the frames, it's a page fault
            if (!frames.contains(page)) {
                pageFaults++;

                // If there is space in frames, add the page
                if (frames.size() < numOfFrames) {
                    frames.add(page);
                } else {
                    // Find the page to replace using the Optimal strategy
                    int farthestIndex = -1;
                    int pageToReplace = -1;

                    for (Integer frame : frames) {
                        // Find the index of the frame in the reference string after the current index
                        int nextUseIndex = findNextUseIndex(referenceString, i, frame);
                        if (nextUseIndex > farthestIndex) {
                            farthestIndex = nextUseIndex;
                            pageToReplace = frame;
                        }
                    }

                    // Replace the page
                    frames.remove(pageToReplace);
                    frames.add(page);
                }
            }
        }

        return pageFaults;
    }

    // Helper method to find the next use index of a page in the reference string
    private static int findNextUseIndex(int[] referenceString, int currentIndex, int page) {
        for (int i = currentIndex + 1; i < referenceString.length; i++) {
            if (referenceString[i] == page) {
                return i; // Return the index where the page will be used next
            }
        }
        return Integer.MAX_VALUE; // Return a large value if the page is not found again
    }
}


































// 1. Concept, Uses, and Purpose of the Optimal Page Replacement Algorithm
// Concept:
// In operating systems, page replacement algorithms manage which pages to retain or remove in memory. The Optimal Page Replacement algorithm is an offline algorithm that aims to minimize page faults by replacing the page that won’t be used for the longest time in the future. Although it is not feasible in practical implementations (since it requires future knowledge), it serves as an ideal baseline for comparing other algorithms.

// Uses:
// This algorithm is used in theoretical analysis to evaluate the efficiency of page replacement policies. By comparing real algorithms (like FIFO, LRU) against the optimal page replacement, systems designers can understand the upper bound on performance.

// Why Use It:
// Although not directly implementable in a live system, the optimal page replacement algorithm helps analyze and benchmark other page replacement strategies. By setting a baseline of minimal page faults, it aids in improving memory management and optimizing the efficiency of system resources.

// 2. Logic and Algorithm of the Code
// Logic:
// The code simulates the Optimal Page Replacement algorithm. It goes through each page in a reference string (which represents the sequence of pages requested by processes) and checks if the page is already in a set of frames:

// If the page is not in the frames and there is space, it is added to avoid a page fault.
// If the frame set is full, the code calculates which page will be used farthest in the future and replaces that page to minimize future page faults.
// Algorithm:
// Initialize variables to track the frames and count page faults.
// Iterate over each page in the reference string:
// If the page is already in frames, continue.
// If not, a page fault occurs.
// If there is space in frames, add the page.
// If the frames are full, use the helper function findNextUseIndex to find the page that will be used farthest in the future.
// Remove the page with the farthest next use and add the new page.
// Return the total number of page faults.
// 3. Line-by-Line Explanation of the Code
// Code:
// java
// Copy code
// import java.util.*;

// public class OptimalPageReplacement {
// Explanation: Imports the necessary libraries for handling sets and user input, then defines the OptimalPageReplacement class.
// java
// Copy code
//     public static void main(String[] args) {
//         Scanner scanner = new Scanner(System.in);
// Explanation: Initializes a Scanner object to take input from the user in the main method.
// java
// Copy code
//         System.out.print("Enter the length of the reference string: ");
//         int length = scanner.nextInt();
// Explanation: Prompts the user to input the length of the reference string and stores it in the variable length.
// java
// Copy code
//         int[] referenceString = new int[length];
//         System.out.println("Enter the reference string (space-separated): ");
//         for (int i = 0; i < length; i++) {
//             referenceString[i] = scanner.nextInt();
//         }
// Explanation: Declares an integer array referenceString to store the sequence of page requests. The program then takes space-separated values as the page reference string from the user.
// java
// Copy code
//         System.out.print("Enter the number of frames: ");
//         int numOfFrames = scanner.nextInt();
// Explanation: Prompts the user to input the number of available frames in memory, storing it in numOfFrames.
// java
// Copy code
//         int pageFaults = calculatePageFaults(referenceString, numOfFrames);
//         System.out.println("Number of Page Faults: " + pageFaults);
//     }
// Explanation: Calls the calculatePageFaults function with the reference string and frame count, then outputs the total page faults.
// java
// Copy code
//     public static int calculatePageFaults(int[] referenceString, int numOfFrames) {
//         Set<Integer> frames = new HashSet<>();
//         int pageFaults = 0;
// Explanation: Defines calculatePageFaults, initializing an empty set frames to store current pages in frames and pageFaults counter.
// java
// Copy code
//         for (int i = 0; i < referenceString.length; i++) {
//             int page = referenceString[i];
// Explanation: Loops through each page in the reference string, storing the current page in the variable page.
// java
// Copy code
//             if (!frames.contains(page)) {
//                 pageFaults++;
// Explanation: Checks if page is in frames. If not, a page fault occurs, so pageFaults is incremented.
// java
// Copy code
//                 if (frames.size() < numOfFrames) {
//                     frames.add(page);
//                 } else {
// Explanation: If frames has room, it simply adds page. Otherwise, it proceeds to the optimal replacement strategy.
// java
// Copy code
//                     int farthestIndex = -1;
//                     int pageToReplace = -1;
// Explanation: Initializes variables to track the page with the farthest next use (farthestIndex) and the pageToReplace.
// java
// Copy code
//                     for (Integer frame : frames) {
//                         int nextUseIndex = findNextUseIndex(referenceString, i, frame);
//                         if (nextUseIndex > farthestIndex) {
//                             farthestIndex = nextUseIndex;
//                             pageToReplace = frame;
//                         }
//                     }
// Explanation: Loops over each page in frames, calling findNextUseIndex to determine the next occurrence of each page in the reference string. It updates pageToReplace to the page that will be used the farthest in the future.
// java
// Copy code
//                     frames.remove(pageToReplace);
//                     frames.add(page);
//                 }
//             }
//         }
// Explanation: Removes pageToReplace from frames and adds the current page.
// java
// Copy code
//         return pageFaults;
//     }
// Explanation: Returns the total page faults.
// java
// Copy code
//     private static int findNextUseIndex(int[] referenceString, int currentIndex, int page) {
//         for (int i = currentIndex + 1; i < referenceString.length; i++) {
//             if (referenceString[i] == page) {
//                 return i;
//             }
//         }
//         return Integer.MAX_VALUE;
//     }
// }
// Explanation: This helper function loops through the reference string from currentIndex + 1 to find the next occurrence of page. If found, it returns the index. If not, it returns Integer.MAX_VALUE, indicating the page won’t be used again.
// 4. Possible Questions and Answers
// Q: What is the Optimal Page Replacement algorithm?

// A: It’s a page replacement strategy that replaces the page that will not be used for the longest period in the future, minimizing page faults. It is ideal and typically used as a theoretical benchmark.
// Q: Why do we use sets in this code?

// A: Sets provide an efficient way to store pages currently in frames and allow fast membership checks. This helps determine if a page fault occurs.
// Q: How is the findNextUseIndex function significant in this algorithm?

// A: findNextUseIndex determines the next occurrence of each page in the reference string, helping identify which page to replace for the optimal page replacement.
// Q: Why is Integer.MAX_VALUE returned in findNextUseIndex if the page is not found?

// A: Returning Integer.MAX_VALUE indicates the page will not be used again, making it a priority candidate for replacement in the Optimal strategy.
// Q: What is a page fault, and why does it occur?

// A: A page fault occurs when the requested page is not found in memory (frames), causing the system to fetch it from secondary storage (e.g., disk). This happens because of insufficient frame space or inefficient replacement strategy.
// Q: Can the Optimal Page Replacement algorithm be implemented practically?

// A: Not typically, as it requires knowledge of future page references, which isn’t possible in real-time systems. It’s used for theoretical benchmarking.
// This breakdown covers each of the required areas in detail, giving you a strong foundation for your exam. Let me know if you have any further questions!