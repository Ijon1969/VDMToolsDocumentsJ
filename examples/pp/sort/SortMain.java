/*
* WHAT
*    Main Java program for the VDM++ sort example
* PROJECT
*    Toolbox
* COPYRIGHT
*    (C) 2012 SCSK
***/

import java.util.List;
import java.util.ArrayList;

public class SortMain
{
  @SuppressWarnings("unchecked")
  public static void main(String[] args)
  {
    try
    {
      //  let arr1 = [3,5,2,23,1,42,98,31],
      //      arr2 = [3,1,2]:
      List arr1 = new ArrayList();
      List arr2 = new ArrayList();
      arr1.add(new Integer(3));
      arr1.add(new Integer(5));
      arr1.add(new Integer(2));
      arr1.add(new Integer(23));
      arr1.add(new Integer(1));
      arr1.add(new Integer(42));
      arr1.add(new Integer(98));
      arr1.add(new Integer(31));
      arr2.add(new Integer(3));
      arr2.add(new Integer(1));
      arr2.add(new Integer(2));

      // dcl smach : SortMachine := new SortMachine(),
      //     res : seq of int = [];
      SortMachine smach = new SortMachine();
      List res = null;

      // def dos : Sorter := new DoSort() in
      // res = smach.SetAndSort(dos,arr1);
      System.out.println("Evaluating DoSort(" + arr1.toString() + "):");
      DoSort dos = new DoSort();
      res = smach.SetAndSort(dos, arr1);
      System.out.println(res.toString());
      System.out.println();

      // def expls  : Sorter := new ExplSort() in
      // res = smach.SetAndSort(expls,arr2);
      System.out.println("Evaluating ExplSort(" + arr2.toString() + "):");
      ExplSort expls = new ExplSort();
      res = smach.SetAndSort(expls, arr2);
      System.out.println(res.toString());
      System.out.println();

      // def imps  : Sorter := new ImplSort() in
      // (res = smach.SetAndSort(imps,arr2)
      //    imps.Post_ImplSorter(arr2,res))
      System.out.println("Evaluating ImplSort(" + arr2.toString() + "):");
      ImplSort imps = new ImplSort();
      res = smach.SetAndSort(imps, arr2);
      System.out.println(res.toString());
      System.out.println();

      System.out.println("Evaluating post condition for ImplSort:");
      Boolean p = imps.post_ImplSorter(arr2, res);
      System.out.println("post_ImplSort(" + arr2.toString() + "," + res.toString() + "):");
      System.out.println(p.toString());
      System.out.println();

      // def mergs : Sorter := new MergeSort() in
      // smach.SetSort(mergs);
      MergeSort mergs = new MergeSort();
      smach.SetSort(mergs);

      // res = smach.GoSorting(arr2);
      System.out.println("Evaluating MergeSort(" + arr2.toString() + "):");
      res = smach.GoSorting(arr2);
      System.out.println(res.toString());
    }
    catch (Exception e) {
      System.out.println(e.getMessage());
    }
  }
}

