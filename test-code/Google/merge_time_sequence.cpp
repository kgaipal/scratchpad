// ----- begin -----
// Given
// struct range {
//   int start_time;
//   int end_time;
// };

// representing a time range [start_time <= time < end_time]

// Write a function which takes two iterators (begin, end) representing an
// unordered sequence of ranges and produces an ordered sequence with the minimum
// number of ranges (i.e. coalescing overlapping ranges).

// Example:
// [3,5] [1,4] [6,9] [11,12] [3,7] [9,10] -> [1,9] [9,10] [11,12]

// [1,4], [2,3] => [1, 4]
// [1,4], [2,5] => [1, 5]
// [1,4], [4,5] =>

// -- solution:
// void merge_time_sequence(List* head)
// {
// // 1. sort them all in ordered by start_time value
// 	  // input: [1,4], [3,5], [3,7], [6,9] [9,10] [11,12]
// // output: [1, 4] [1, 3] => [1,3] [1,4]
// // [3,5] [1,4] => [1,4]  [3,5] => [1, 5]
// head = sort_by_time(head);

// // 2. start merging with overlapping
// // first node to compare is first and second in consideration is second
// if (second->start_time < first->end_time)
// {
//     // overlap

// if (first>end_time > second->end_time)
// {
// // [ first->start_time, first->end_time]
// } else
// {
// // [first->start_time, second->end_time]
// }
// // continue a, b ,c and a,b are merged, start again with [a+b] to compare with c, delete b
// }
// else
// {
// // leave as it is since no overlap: advance to next item by one
// }
// }
// ---- end ----

// my solution again:
