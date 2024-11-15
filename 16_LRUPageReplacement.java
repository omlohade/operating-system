import java.util.*;

public class LRUPageReplacement {

    public static int calculatePageFaults(int[] referenceString, int frameCount) {
        Set<Integer> frames = new HashSet<>();
        Map<Integer, Integer> lruMap = new HashMap<>();
        int pageFaults = 0;
        int time = 0; // To keep track of the time each page was last used

        for (int page : referenceString) {
            // Check if the page is not in frames (page fault)
            if (!frames.contains(page)) {
                pageFaults++;
                
                // If frames are full, find the least recently used page to replace
                if (frames.size() == frameCount) {
                    // Find the LRU page based on minimum last used time
                    int lruPage = Collections.min(lruMap.entrySet(), Map.Entry.comparingByValue()).getKey();
                    frames.remove(lruPage);
                    lruMap.remove(lruPage);
                }
                
                // Add the new page to frames and update last used time
                frames.add(page);
            }
            
            // Update the last used time for the current page
            lruMap.put(page, time++);
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

        // Calculate page faults using LRU
        int pageFaults = calculatePageFaults(referenceString, frameCount);
        
        // Output the number of page faults
        System.out.println("Total page faults using LRU: " + pageFaults);
    }
}

/*
Enter the number of pages in the reference string: 12
Enter the pages in the reference string:
1 3 0 3 5 6 3 1 3 6 1 2
Enter the number of page frames: 3

Output:
Total page faults using LRU: 9

*/























// 1. Explain Concept, Its Use, and Why We Use It:
// Page Replacement is a mechanism in memory management that deals with the problem of handling page faults in systems with limited physical memory. When a process requests a page that is not in memory, a page fault occurs, and a page replacement algorithm is used to decide which page to remove from memory to load the new one.

// LRU (Least Recently Used) is a page replacement algorithm that replaces the page that has not been used for the longest time. The idea behind LRU is that pages that have been used recently are more likely to be used again soon, so they should be kept in memory, while pages that haven't been used recently should be replaced first.

// Use of LRU:

// LRU attempts to approximate optimal page replacement by evicting the least recently used page, based on the assumption that pages used in the past will likely be used again soon.
// It is commonly used in real-world applications where access patterns are somewhat predictable or exhibit temporal locality.
// 2. Explain Logic of the Algorithm:
// The algorithm works by keeping track of the order in which pages are used. When a page fault occurs:

// Page Fault Detection: If the page is not found in memory (frames), it counts as a page fault.
// Frame Management:
// If there is space in memory (i.e., the number of frames is not full), the page is simply added to the frames.
// If memory is full, the LRU page (the one that was used the least recently) is evicted, and the new page is added to memory.
// Track Last Access Time: A Map (or hash table) is used to track the last time each page was accessed. The page with the smallest timestamp (oldest accessed) is considered the least recently used.
// 3. Explain Code Line by Line:
// java
// Copy code
// public class LRUPageReplacement {
// Defines the LRUPageReplacement class.
// java
// Copy code
// public static int calculatePageFaults(int[] referenceString, int frameCount) {
//     Set<Integer> frames = new HashSet<>();
//     Map<Integer, Integer> lruMap = new HashMap<>();
//     int pageFaults = 0;
//     int time = 0; // To keep track of the time each page was last used
// This method calculates the number of page faults using the LRU algorithm.
// frames keeps track of pages currently in memory.
// lruMap stores the last access time of each page. The page with the smallest timestamp is the least recently used.
// pageFaults counts the total page faults.
// time is used to incrementally track when each page was last used.
// java
// Copy code
// for (int page : referenceString) {
//     if (!frames.contains(page)) {
//         pageFaults++;
// For each page in the reference string, check if the page is not already in memory (!frames.contains(page)). If it's not, a page fault occurs, and the pageFaults counter is incremented.
// java
// Copy code
//         if (frames.size() == frameCount) {
//             int lruPage = Collections.min(lruMap.entrySet(), Map.Entry.comparingByValue()).getKey();
//             frames.remove(lruPage);
//             lruMap.remove(lruPage);
//         }
// If memory is full (frames.size() == frameCount), find the least recently used page:
// Use Collections.min() to find the entry in lruMap with the smallest value (oldest access time).
// Remove the LRU page from both the frames set and the lruMap.
// java
// Copy code
//         frames.add(page);
//     }
    
//     lruMap.put(page, time++);
// }
// Add the new page to the frames set.
// Update the last access time for the current page in lruMap. The time variable is incremented to track the page's last usage.
// java
// Copy code
// return pageFaults;
// Returns the total count of page faults.
// java
// Copy code
// public static void main(String[] args) {
//     Scanner sc = new Scanner(System.in);
// The main method where user inputs are taken using Scanner.
// java
// Copy code
//     System.out.print("Enter the number of pages in the reference string: ");
//     int n = sc.nextInt();
//     int[] referenceString = new int[n];
// Takes the number of pages and initializes the referenceString array.
// java
// Copy code
//     System.out.println("Enter the pages in the reference string:");
//     for (int i = 0; i < n; i++) {
//         referenceString[i] = sc.nextInt();
//     }
// Takes the pages in the reference string from the user.
// java
// Copy code
//     System.out.print("Enter the number of page frames: ");
//     int frameCount = sc.nextInt();
// Takes the number of frames (memory slots) from the user.
// java
// Copy code
//     int pageFaults = calculatePageFaults(referenceString, frameCount);
// Calls the calculatePageFaults method with the reference string and frame count to calculate the page faults.
// java
// Copy code
//     System.out.println("Total page faults using LRU: " + pageFaults);
// }
// Prints the total number of page faults calculated using the LRU algorithm.
// 4. Potential Questions from Examiner:
// What is LRU (Least Recently Used) page replacement, and how does it work?

// LRU is a page replacement algorithm that removes the least recently used page from memory when a new page needs to be loaded, assuming that pages used recently will be used again soon. It tracks the access time of each page and evicts the page with the oldest timestamp.
// How does the algorithm track the last used time for each page?

// The algorithm uses a Map (or hash table) where the key is the page number, and the value is the timestamp representing the last access time. The page with the smallest timestamp is considered the least recently used.
// What happens when a page is referenced that is not in memory?

// When a page is referenced that is not currently in memory, a page fault occurs. If there is space in memory, the page is added directly. If memory is full, the least recently used page is evicted to make room for the new page.
// How does the algorithm handle page eviction when memory is full?

// If memory is full, the algorithm identifies the page with the oldest access time (least recently used) using the lruMap, removes it from both the frames set and lruMap, and loads the new page into memory.
// What is the time complexity of this LRU page replacement algorithm?

// The time complexity of this implementation is 
// 𝑂
// (
// 𝑛
// ×
// log
// ⁡
// 𝑛
// )
// O(n×logn), where 
// 𝑛
// n is the number of pages in the reference string. This complexity arises because for each page reference, the algorithm may need to find the least recently used page in 
// 𝑂
// (
// log
// ⁡
// 𝑛
// )
// O(logn) time using Collections.min().
// How does this algorithm compare to FIFO or Optimal page replacement?

// LRU generally performs better than FIFO since it tries to retain pages that are used more frequently. However, it can be more computationally expensive because it requires tracking access times for each page. It also tends to perform worse than the Optimal Page Replacement algorithm, which knows the future page reference sequence and can always replace the page that will not be used for the longest time.
// What would happen if pages were referenced in a sequential pattern?

// In a sequential reference pattern, LRU would likely have high page fault rates since each page would be evicted immediately after it is used. For this case, FIFO might perform better, as it does not rely on access time.
// Can this algorithm be improved? How?

// The performance of this algorithm could be improved by using more efficient data structures for tracking the least recently used page, such as a doubly linked list combined with a hash map, reducing the complexity of finding the LRU page to 
// 𝑂
// (
// 1
// )
// O(1). This would optimize both the time to update the last access times and to remove the least recently used page.
// How would the algorithm behave if memory was underutilized (less than frameCount pages used)?

// If memory is underutilized, LRU would simply load the new pages into memory until it is full, without evicting any pages until the number of frames is reached.