//#include "stdafx.h"
//#include <iostream> 
//using namespace std;
//=================
#include <stdio.h>
//======================== VERTEX ==========================
class Vertex
{
    public:
      int Value;
      bool Hit;
      Vertex() { Value = 0; Hit = false; }
      Vertex(int val) { Value = val; Hit = false; }
};
//======================== STACK ===========================
template <class T>
class Stack
{
     class Node
     {
          public:
          T value;
          Node* prev;

          Node(T val=0)
          {
              value = val;
              prev = NULL;
          }
     };
     int stackSize;
     Node* head;
     
     public:
     Stack()
     {
          head = NULL;
          stackSize = 0;
     }

     int size();       //-- получить размер стека
     void push(T val); //-- поместить элемент на верх стека.
     void empty();     //-- опустошить стек
     T pop();          //-- извлечь последний установленный в стек элемент.
     T peek();         //-- получить верхний элемент стека, не удаляя его.     
};
Stack<Vertex*> stack;

   template <class T> void Stack<T> :: push(T val)
   {     Node *node = new Node(val);
         if (head == NULL)             //если это первый элемент
            node -> prev = NULL;
         else
            node -> prev = head;

         head = node;
         stackSize += 1;
   }

   template <class T> int Stack<T>:: size()
   {    return stackSize;
   }

   template <class T> T Stack<T>:: pop()
   {   if(head != NULL)
         {
            T val = head->value;
            head = head->prev;
         stackSize -= 1;
         return (val);
         }
         return NULL;
   }

   template <class T> T Stack<T> :: peek()
   {     if(head !=NULL)
         {
            T val = head->value;
            return (val);
         }
         return NULL;
   }

   template <class T> void Stack<T>:: empty()
   {   while(pop() != NULL) {}
   }

//=====================SIMPLE GRAPH===========================  
class SimpleGraph
{
    public:
      Vertex* vertex;      
      int** m_adjacency;
      int max_vertex;
	
      SimpleGraph(int size)
      {
        max_vertex = size;
        m_adjacency = new int*[size];
        for(int i = 0; i < size; i++) 
        {  m_adjacency[i] = new int[size];
           for(int j = 0; j < size; j++)
             m_adjacency[i][j] = -1;  
        } 
        vertex = new Vertex [size];
      }
	
      void AddVertex(int value)
      { 
        for(int i = 0; i < max_vertex; i++)
        {
           if (m_adjacency[i][i] == -1) // looking for "empty" vertex slot 
           {
              vertex[i].Value = value; // присваиваем новое значение
              for(int j = 0; j < max_vertex; j++) // настраиваем связи
              {
                 m_adjacency[i][j] = 0;
                 m_adjacency[j][i] = 0;                 
              }
              return;
           }
        } 
      }

      void RemoveVertex(int v)    // remove the vertex with all its edges
      {        
        for(int i = 0; i < max_vertex; i++) 
        {  m_adjacency[v][i] = 0; // edges remove 
           m_adjacency[i][v] = 0;
        }
        m_adjacency[v][v] = -1;   // vertex remove      
      }
	
      bool IsEdge(int v1, int v2) 
      {        
        if (v1 >= max_vertex || v2 >= max_vertex || m_adjacency[v1][v1] == -1 ||  m_adjacency[v2][v2] == -1 )
           return false;          // if array size exceeded or no vertex by this index
        if ( (m_adjacency[v1][v2] == 1) && (m_adjacency[v2][v1] == 1) )
           return true;
        return false;
      }

      bool IsVertex(int v) 
      {        
        if (v >= max_vertex || m_adjacency[v][v] == -1)
           return false;          // if array size exceeded or no vertex by this index        
        return true;        
      }
	
      void AddEdge(int v1, int v2)
      { 
        if (v1 >= max_vertex || v2 >= max_vertex || m_adjacency[v1][v1] == -1 ||  m_adjacency[v2][v2] == -1 )
           return;               // if array size exceeded or no vertex by this index
        m_adjacency[v1][v2] = 1; // set edge
        m_adjacency[v2][v1] = 1;
      }
	
      void RemoveEdge(int v1, int v2)
      {
        if (v1 >= max_vertex || v2 >= max_vertex || m_adjacency[v1][v1] == -1 ||  m_adjacency[v2][v2] == -1 )
           return;               // if array size exceeded or no vertex by this index
        m_adjacency[v1][v2] = 0; // set edge
        m_adjacency[v2][v1] = 0;
      }
   
      int FindVertex (int value)
      {
        for(int i = 0; i < max_vertex; i++) 
        {  if(vertex[i].Value == value) // ищем вершину v1
           {  if ( m_adjacency[i][i] != -1 ) 
                 return i; 
        }  } 
        return -1;
      }

    Vertex** DepthFirstSearch(int VFrom, int VTo)
    {
       while(stack.peek() != NULL) 
       {
         Vertex* from_stack = stack.pop();
         from_stack->Hit = false;
       }

       white_to_stack(VFrom, VTo); // запись стека      
       int size = stack.size();

       if(size != 0)
       {          
          Vertex** way = new Vertex* [size+1];
          for (int i = size-1; i >= 0; i--)
          {
             way[i] = stack.pop();
          }
          way[size] = NULL;
          return way;
       }
       else 
          return NULL;
      // Узлы задаются позициями в списке vertex.
      // Возвращается список узлов -- путь из VFrom в VTo.
      // Список завершается NULL-ом
    }

    void white_to_stack(int VFrom, int VTo)
    {
      vertex[VFrom].Hit = true;  // Фиксируем вершину X как посещённую
      stack.push(&vertex[VFrom]);// Помещаем вершину X в стек

      if(IsEdge(VFrom, VTo) == true)
      {
         stack.push(&vertex[VTo]);
         return;
      }
      else
      {
         for(int i = 0; i <= max_vertex; i++) // обход вершин
         {
            if (IsVertex(i) && vertex[i].Hit == false && IsEdge(VFrom, i) == true) // вершина есть & она не посещена & есть ребро
            {
               white_to_stack(i, VTo);     // то повторяем                
            }
            if (stack.peek() == vertex + VTo)
               return;
            if (i == max_vertex)
               stack.pop(); //удаляем верхнюю вершину 
         }         
      }
    }
};
//=====================================================================================
void test()
{
   int test = 0;
   int V1 = 4;
   int V2 = 2;
   int V3 = 0;
	
   SimpleGraph Graph(3);
   for(int i = 0; i < Graph.max_vertex; i++)  // проверка правильности создания таблицы       
   {  for(int j = 0; j < Graph.max_vertex; j++) 
      {  if (Graph.m_adjacency[i][j] != -1) 
            test ++; 
      } 
   }   

   Graph.AddVertex(V1);

   int v1 = Graph.FindVertex(V1);        // правильность создания изолированной вершины
   if (v1 != 0) test++;
   for(int i = 0; i < Graph.max_vertex; i++) 
   {  if ( (Graph.m_adjacency[v1][i] != 0) && (Graph.m_adjacency[i][v1] != 0) )
         test++; 
   }
               
   Graph.AddVertex(V2);
   int v2 = Graph.FindVertex(V2);
   if (v2 != 1) test++;
   if (Graph.vertex[v2].Value != V2) test;
   for(int i = 0; i < Graph.max_vertex; i++) 
   {  if ( (Graph.m_adjacency[v2][i] != 0) && (Graph.m_adjacency[i][v2] != 0) )
         test++; 
   }

   if(Graph.IsEdge(v1, v2) != false) test++;
   Graph.AddEdge(v1, v2);
   if(Graph.IsEdge(v1, v2) != true) test++;


   Graph.AddEdge(v2, 3);  // array size exceeded 
   if(Graph.IsEdge(v2, 3) != false) test++;
   Graph.AddEdge(v2, 2);  // no vertex by this index 
   if(Graph.IsEdge(v2, 2) != false) test++;


   Graph.AddVertex(V3);
   int v3 = Graph.FindVertex(V3);
   if (v3 != 2) test++;
   for(int i = 0; i < Graph.max_vertex; i++) 
   {  if ( (Graph.m_adjacency[v3][i] != 0) && (Graph.m_adjacency[v3][i] != 0) )
         test++; 
   }

   if(Graph.IsEdge(v2, v3) != false) test++;
   Graph.AddEdge(v2, v3);
   if(Graph.IsEdge(v2, v3) != true) test++;

   if(Graph.IsEdge(v2, v2) != false) test++;
   Graph.AddEdge(v2, v2);
   if(Graph.IsEdge(v2, v2) != true) test++; 

   Graph.RemoveEdge(v2,v2);
   if(Graph.IsEdge(v2, v2) != false) test++;

   Graph.RemoveVertex(v3);
   if(Graph.FindVertex(V3) != -1) test++;
   for(int i = 0; i < Graph.max_vertex; i++) 
   {  if ( Graph.IsEdge(i, v3) != false )
         test++; 
   }
   Graph.RemoveVertex(v2);
   Graph.RemoveVertex(v1);
   //-----------------------------------------
   //cout << endl;  // проверка правильности создания таблицы  
   //for(int i = 0; i < Graph.max_vertex; i++)   
   //{
   //   for(int j = 0; j < Graph.max_vertex; j++)
   //   {
   //      cout << Graph.m_adjacency[i][j] << "    " ;
   //   }
   //   cout << endl;
   //}
   //cout << endl << "Test result: " << test << endl << endl;
   //-----------------------------------------
   SimpleGraph Graph2(5);
   Graph2.AddVertex(0);
   Graph2.AddVertex(1);
   Graph2.AddVertex(2);
   Graph2.AddVertex(3);
   Graph2.AddVertex(4);
   Graph2.AddEdge(0, 1);
   Graph2.AddEdge(0, 2);
   Graph2.AddEdge(1, 3);
   Graph2.AddEdge(2, 4);
   Vertex** way = Graph2.DepthFirstSearch(0, 4);
   //-----------------------------------------
   //cout << endl;  // проверка правильности создания таблицы  
   //for(int i = 0; i < Graph2.max_vertex; i++)   
   //{
   //   for(int j = 0; j < Graph2.max_vertex; j++)
   //   {
   //      cout << Graph2.m_adjacency[i][j] << "    " ;
   //   }
   //   cout << endl;
   //}
   //cout << endl;
   //for(Vertex** i = way; *i != NULL; i++)   
   //{
   //   Vertex* n = *i;
   //   cout << n->Value << endl;
   //}
   //cout << endl;
}

//void main()
//{
//   test();
//   system("pause");
//}

