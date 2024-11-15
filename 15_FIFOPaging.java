import java.util.*;

public class FIFOPaging {

    public static int calculatePageFaults(int[] referenceString, int frameCount) {
        Set<Integer> frames = new HashSet<>();
        Queue<Integer> fifoQueue = new LinkedList<>();
        int pageFaults = 0;

        for (int page : referenceString) {
            // Check if page is already in one of the frames
            if (!frames.contains(page)) {
                // Page fault occurs
                pageFaults++;
                
                // If there is no empty frame, remove the oldest page (FIFO order)
                if (frames.size() == frameCount) {
                    int oldestPage = fifoQueue.poll();
                    frames.remove(oldestPage);
                }
                
                // Add the new page to frames and FIFO queue
                frames.add(page);
                fifoQueue.add(page);
            }
        }
        return pageFaults;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input for reference string
        System.out.print("Enter the number of pages in the reference string: ");
        int n = sc.nextInt();
        int[] referenceString = new int[n];
        
        System.out.println("Enter the pages in the reference string:");
        for (int i = 0; i < n; i++) {
            referenceString[i] = sc.nextInt();
        }

        // Input for number of frames
        System.out.print("Enter the number of page frames: ");
        int frameCount = sc.nextInt();

        // Calculate page faults using FIFO
        int pageFaults = calculatePageFaults(referenceString, frameCount);
        
        // Output the number of page faults
        System.out.println("Total page faults using FIFO: " + pageFaults);
    }
}










// 1. Explain Concept, Its Use, and Why We Use It:
// Paging is a memory management scheme that eliminates the need for contiguous allocation of physical memory. In this system, the physical memory is divided into fixed-sized blocks called frames, and the logical memory (or process memory) is divided into blocks of the same size, called pages.

// When a process needs to access a page, it is loaded into one of the frames in memory. If the page is not already loaded in memory, a page fault occurs, which leads to the replacement of an existing page in memory. Page replacement algorithms are used to decide which pages to remove from memory to make space for new ones.

// FIFO (First-In, First-Out) is one of the simplest page replacement algorithms. It works by replacing the oldest page in memory when a page fault occurs and there are no free frames available. FIFO treats the page entries in memory as a queue where the first page to be loaded is the first one to be replaced.

// Use of FIFO:

// FIFO is simple to implement and understand.
// It works well for certain types of workloads, especially when pages are referenced in a predictable manner.
// 2. Explain Logic of the Algorithm:
// FIFO (First-In, First-Out) operates by keeping track of the pages in memory using a queue. When a page is referenced:
// Check for page fault: If the page is not already in memory (not in the frame set), a page fault occurs.
// Handle the page fault:
// If there is an empty frame, simply load the new page.
// If there is no empty frame, evict the oldest page (the one that has been in memory the longest) by removing the first page in the queue.
// Add the new page to the memory and the queue.
// Count the page faults and continue until all pages in the reference string are processed.
// 3. Explain Code Line by Line:
// java
// Copy code
// public class FIFOPaging {
// Defines the FIFOPaging class.
// java
// Copy code
// public static int calculatePageFaults(int[] referenceString, int frameCount) {
//     Set<Integer> frames = new HashSet<>();
//     Queue<Integer> fifoQueue = new LinkedList<>();
//     int pageFaults = 0;
// This method calculates the number of page faults using the FIFO algorithm.
// A Set is used to track pages currently in memory (frames) to ensure unique entries.
// A Queue (fifoQueue) is used to keep track of the order in which pages are loaded into memory (for FIFO eviction).
// pageFaults keeps count of the number of page faults.
// java
// Copy code
// for (int page : referenceString) {
//     if (!frames.contains(page)) {
//         pageFaults++;
// Iterates over the referenceString (the sequence of pages).
// If the page is not found in the current frames (!frames.contains(page)), a page fault occurs and the pageFaults counter is incremented.
// java
// Copy code
//         if (frames.size() == frameCount) {
//             int oldestPage = fifoQueue.poll();
//             frames.remove(oldestPage);
//         }
// If the frame is full (i.e., the number of pages in memory equals frameCount), the oldest page is removed from memory by:
// Polling the queue (FIFO order).
// Removing the oldest page from the frames set.
// java
// Copy code
//         frames.add(page);
//         fifoQueue.add(page);
//     }
// }
// After removing the oldest page (if necessary), the new page is added to both the frames set and the fifoQueue.
// java
// Copy code
// return pageFaults;
// Returns the total count of page faults.
// java
// Copy code
// public static void main(String[] args) {
//     Scanner sc = new Scanner(System.in);
// The main method where user inputs are collected using Scanner.
// java
// Copy code
//     System.out.print("Enter the number of pages in the reference string: ");
//     int n = sc.nextInt();
//     int[] referenceString = new int[n];
// Prompts the user to enter the number of pages and initializes the referenceString array with the entered size.
// java
// Copy code
//     System.out.println("Enter the pages in the reference string:");
//     for (int i = 0; i < n; i++) {
//         referenceString[i] = sc.nextInt();
//     }
// Takes the actual page reference string from the user.
// java
// Copy code
//     System.out.print("Enter the number of page frames: ");
//     int frameCount = sc.nextInt();
// Takes the number of frames (memory slots) from the user.
// java
// Copy code
//     int pageFaults = calculatePageFaults(referenceString, frameCount);
// Calls calculatePageFaults with the entered reference string and frame count to calculate the page faults.
// java
// Copy code
//     System.out.println("Total page faults using FIFO: " + pageFaults);
// }
// Prints the total number of page faults calculated by the FIFO algorithm.
// 4. Potential Questions from Examiner:
// What is FIFO, and why is it used for page replacement?

// FIFO is a page replacement algorithm that replaces the oldest page in memory when a page fault occurs. It is simple to implement and easy to understand. FIFO is useful in situations where a predictable or regular sequence of page references is observed, but it may not always perform optimally in complex workloads.
// What is a page fault, and how is it handled in this algorithm?

// A page fault occurs when a process requests a page that is not currently in memory. In this algorithm, if a page fault occurs, the oldest page is evicted from memory if no frames are available, and the new page is loaded into memory.
// Why is a Set used to track pages in memory, and why is a Queue used?

// The Set ensures that each page is unique and that we can efficiently check whether a page is in memory. The Queue tracks the order of pages, allowing us to remove the oldest page when a page fault occurs, adhering to the FIFO principle.
// How does this algorithm behave when the reference string contains repeated pages?

// When a page is referenced again, and it is already in memory, it does not count as a page fault. The algorithm simply moves to the next page in the reference string without making any changes to the frames.
// What would happen if the number of frames (frameCount) is greater than or equal to the number of unique pages in the reference string?

// If the number of frames is greater than or equal to the number of unique pages, no page faults would occur after the initial loading of pages, as all pages can fit into memory.
// What are the advantages and disadvantages of the FIFO page replacement algorithm?

// Advantages: Simple to implement and understand. Efficient for small, predictable workloads.
// Disadvantages: It does not always provide optimal page replacement, leading to higher page fault rates in some cases (for example, the Belady's anomaly where increasing the number of frames can increase the number of page faults).
// How would you modify this program to implement another page replacement algorithm, such as Least Recently Used (LRU)?

// To implement LRU, you would need to track the order in which pages are accessed, not just the order they were loaded. A linked list or a hashmap with a doubly linked list can be used to track the most recently used pages, replacing the least recently used page when a page fault occurs.
// What is the time complexity of the FIFO page replacement algorithm in this implementation?

// The time complexity for this implementation is 
// 𝑂
// (
// 𝑛
// ×
// 𝑚
// )
// O(n×m), where 
// 𝑛
// n is the number of pages and 
// 𝑚
// m is the number of frames. For each page, we check if it is in the set of frames (which is 
// 𝑂
// (
// 1
// )
// O(1) on average) and perform a queue operation to remove the oldest page and add the new page (which are 
// 𝑂
// (
// 1
// )
// O(1) operations). However, removing from the set and adding to the queue both require constant time operations due to their efficient underlying data structures.