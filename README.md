# 📚 Sorting Algorithms Visualization (SFML)
A fun and interactive project to learn and visualize six popular sorting algorithms using SFML.
Each algorithm is visualized with comparisons, array accesses, and delay settings to better understand how sorting actually works!

### ✨ Features
 <ol> <li>Visualize six major sorting algorithms: 
   <b><ul>
     <li>Bubble Sort</li>
     <li>Insertion Sort</li> 
     <li>Selection Sort</li>
     <li>Quick Sort</li> 
     <li>Merge Sort</li>
     <li>Radix Sort</li>
   </ul></b></li>

<li>Real-time stats:
  <ul>
    <li><b>Comparisons</b></li>
    <li><b>Array Access</b></li>
  </ul>
</li>

<li>Color-coded bars for better understanding:
  <ul>
     <li><b>⚪ Unaffected elements.</b></li>
     <li><b>🟢 Found found.</b></li>
    <li><b>🔴 Selected Element for comparison.</b></li>
    <li><b>🔵 Target element</b></li>
    <li><b>🟡 Temporary processing color</b></li>
  
  </ul>
</li>
<li>Smooth, animated transitions powered by SFML.</li>
</ol>

### 🫧 Bubble Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Bubble_Sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Repeatedly compares and swaps adjacent elements if they are in the wrong order.</li>
     <li>Time Complexity:<b>O(n²)</b></li>
     <li>Space Complexity: <b>O(1)</b></li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Understand how adjacent swaps gradually push the largest element to the end.</li>
     <li>Good for understanding basic sorting concepts but not efficient for large data.</li>
    <li>It is <b>"In-Place"</b> sorting algorithm means it doesn't take extra memory for sorting</li>
   </ul>
</li>
</ol>

### 🪡 Insertion Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Insertion_sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Builds the sorted array one item at a time by comparing and inserting into its correct position.</li>
     <li>Time Complexity:<b>O(n²)</b></li>
     <li>Space Complexity: <b>O(1)</b></li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Realized how efficient it is for small datasets.</li>
     <li>It is also <b>"In-Place"</b> sorting algorithm.</li>
   </ul>
</li>
</ol>

###  🏆 Selection Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Selection_sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Selects the minimum element and places it at the beginning.</li>
     <li>Time Complexity:<b>O(n²)</b></li>
     <li>Space Complexity: <b>O(1)</b></li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Saw the importance of minimizing swaps compared to Bubble Sort.</li>
     <li>It is also <b>"In-Place"</b> sorting algorithm.</li>
   </ul>
</li>
</ol>


###  🌀 Merge Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Merge_Sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Divides the array into halves, sorts each half, then merges them.</li>
     <li>Time Complexity:<b>O(n log n)</b></li>
     <li>Space Complexity: 
       <ol>
         <li>In-Place Merge sort: <b>O(1)</b></li>
         <li>Out-Of-Place Merge sort: <b>O(n)</b></li>
       </ol>
       </li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Powerful concept of recursion and merging.</li>
     <li>Great way to learn about <b>stable sorting.</b></li>
   </ul>
</li>
</ol>


### ⚡Quick Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Quick_sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Picks a <b>pivot</b>, <b>partitions the array</b>, and <b>recursively sorts partitions.</b></li>
     <li>Time Complexity:<b>O(n log n)</b></li>
     <li>Space Complexity: <b>O(n)</b></li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Understood <b>divide-and-conquer</b> strategy deeply.</li>
     <li>Visualizing partitioning helped solidify recursion concepts.</li>
   </ul>
</li>
</ol>


###  🎰 Radix Sort

![Image](https://github.com/Imran1720/Sorting-Stick/blob/bbbda9b0f998216b3803cc709af017f6e28fdd8d/Attachments/Radix_sort.gif)

 <ol> <li><b>Details:</b>
   <ul>
     <li>Sorts numbers digit by digit starting from the least significant digit.</li>
     <li>Time Complexity:<b>O(nk) </b>(where <b>k</b> = number of digits)</li>
     <li>Space Complexity: <b>O(n+k)</b></li>
   </ul>
 </li>
   
  <li><b>What I Learned:</b>
  <ul>
     <li>Fascinated by non-comparative sorting.</li>
     <li>Showed how sorting can be achieved without direct element comparisons</li>
   </ul>
</li>
</ol>

### ⚙️Tools Used
 <ul> 
  <li><b>C++</li>
  <li>SFML</b> (Simple and Fast Multimedia Library)</li>
 </ul>

 ### 🎯 Conclusion
Through this project, I realized that <b>seeing algorithms in action</b> is one of the best ways to understand them deeply.
Each algorithm has its strengths and weaknesses depending on the situation.
This project helped me move from theoretical understanding to <b>visual intuition.</b>
