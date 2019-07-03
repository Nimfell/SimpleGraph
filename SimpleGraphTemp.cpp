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
     {  public:
          T value;
          int depth;
          Node* prev;
          Node(T val=0) { value = val; prev = NULL; depth = -1;}
     };
     int stackSize;
     Node* head;

   public:
     Stack() { head = NULL; stackSize = 0; }

     int size();       //-- получить размер стека
     void push(T val); //-- поместить элемент на верх стека.
     void push(T val, int d); 
     void empty();     //-- опустошить стек
     T pop();          //-- извлечь последний установленный в стек элемент.
     T peek();         //-- получить верхний элемент стека, не удаляя его. 
     int depth(); //-- глубина последнего элемента
};
Stack<Vertex*> stack;

   template <class T> void Stack<T> :: push(T val)
   {     Node *node = new Node(val);
         if (head == NULL)             // если это первый элемент
            node -> prev = NULL;
         else
            node -> prev = head;
         head = node;
         stackSize += 1;
   }

   template <class T> void Stack<T> :: push(T val, int d)
   {     Node *node = new Node(val);
         node->depth = d;        // запись глубины
         if (head == NULL)       // если это первый элемент
            node -> prev = NULL;
         else
            node -> prev = head;
         head = node;
         stackSize += 1;
   }

   template <class T> int Stack<T>:: size()
   {    return stackSize;   }

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

   template <class T> int Stack<T>:: depth()
   {     if(head !=NULL)                     
            return head->depth;         
         return 0;
   }


//======================== QUEUE ===========================
template <class T>
class Queue
{
      class Node
      { public:
           T value;
           Node* next;
           int depth;
           Node(T val=0) { value = val; next = NULL; depth = -1;}          
      };
  public:
      Node* head;
      Node* end;
      int Size;
      
      Queue()
      {   head = NULL;
          end = NULL;
          Size = 0;
      }
      void push(T item); // помещаем в очередь
      void push(T item, int d); 
      T pop();           // забираем из очереди
      T peek();          // кто следующий?
      int size();        // размер
      void empty();      // отчистить
      int depth();
};
Queue<Vertex*> queue;

template <class T> void  Queue<T> :: push(T item)
{
   Node *node = new Node(item);   
   if (Size != 0)
      end->next = node;
   end = node;
   if (head == NULL)
      head = node;
   Size ++;   
}

template <class T> void  Queue<T> :: push(T item, int d)
{
   Node *node = new Node(item);
   node->depth = d; // запись глубины
   if (Size != 0)
      end->next = node;
   end = node;
   if (head == NULL)
      head = node;
   Size ++;   
}

template <class T> T Queue<T> :: pop()
{
   if (size() == 0) 
      return NULL;   // if queue is empty
   T t = head->value;
   head = head->next;
   Size --;
   return t;
}

template <class T> T Queue<T> :: peek()
{
   if (size() == 0) 
      return NULL;   // if queue is empty
   T t = head->value;
   return t;
}

template <class T> int Queue<T> :: size()
{ return Size; }  

template <class T> void Queue<T> :: empty()
{
   while(queue.peek() != NULL) 
            queue.pop();
}

template <class T> int Queue<T>:: depth()
{     if(head !=NULL)                     
         return head->depth;         
      return 0;
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
         clear_all_containers();     // опустошаем контейнеры
         white_to_stack(VFrom, VTo); // запись стека   

         int size = stack.size();
         if(size != 0)
         {  Vertex** way = new Vertex* [size+1];
            for (int i = size-1; i >= 0; i--)
               way[i] = stack.pop();            
            way[size] = NULL;
            return way;
         }
         else 
            return NULL;
      // Узлы задаются позициями в списке vertex.
      // Возвращается список узлов -- путь из VFrom в VTo.
      // Список завершается NULL-ом
      }

      Vertex** BreadthFirstSearch(int VFrom, int VTo)
      {
         clear_all_containers();              // опустошаем контейнеры
         white_to_queue(VFrom, VTo, 0);       // запись в очередь вплоть до искомой вершины

         Vertex* last = stack.peek();         // указатель на последний элемент стека
         int Vlast = FindVertex(last->Value); // записываем индекс вершины
         //-- перекладываем из стека в way проверяя путь обратно ------------------------------------
         if ( Vlast == VTo )                  // если последнее вошедшее в стек - искомая вершина то:
         {                                     
            int depht = stack.depth();        // находим глубину искомого элемента            
            queue.empty();                    // отчищаем очередь
            queue.push(stack.pop());          // закладываем в очередь путь от искомой в исходную вершину  
            Vertex* pre_last;   
            while (stack.peek() != NULL)      // пока стек заполнен
            {
               pre_last = stack.peek();   
               //-- если глубина подходящая и есть связь с последней найденной вершиной в пути --
               if (stack.depth() == (depht - 1) && IsEdge( FindVertex(last->Value), FindVertex(pre_last->Value) ) )
               {
                  queue.push(stack.peek());   // кидаем в очередь очередную вершину оптимального пути
                  depht--;
                  last = pre_last;
               }
               //last = pre_last;
               stack.pop();
            }   
            int size = queue.size();
            if(size != 0)
            {  Vertex** way = new Vertex* [size+1];
               for (int i = size-1; i >= 0; i--)
                  way[i] = queue.pop();            
               way[size] = NULL;
               return way;
            } 
         }          
         return NULL;
      }
            
      Vertex** WeakVertices() // возвращает список узлов вне треугольников
      {
         int* vertexes = new int[max_vertex + 1];
         int count_way = 0;
         Vertex** way = new Vertex* [max_vertex+1];
         find_vert(0, way, vertexes, count_way);
         return way;
      }

   private:
      void find_vert(int Vert, Vertex** way, int* vertexes, int count_way)
      {
         if (Vert < max_vertex)
         {            
            int count_vertexes = 0;
            for(int i = 0; i < max_vertex; i++) // находим все связанные вершины
            {  
               if ( IsEdge(Vert, i) ) 
               {               
                  vertexes[count_vertexes++] = i; // сохранили индекс 
               }              
            }
            vertexes[count_vertexes++] = -1;
         
            for (int* i = vertexes; *i != -1; i++) // определяем их связь друг с другом
            {
               for (int* j = vertexes; *j != -1; j++)
               {            
                  if ( IsEdge(*i, *j) ) 
                  {
                     find_vert(Vert+1, way, vertexes, count_way); // переход к следующей вершине 
                     return;
                  } 
               }
            }
            way[count_way++] = &vertex[Vert];
            find_vert(Vert+1, way, vertexes, count_way); // переход к следующей вершине 
            return;
         }
         way[count_way] = NULL;
         delete vertexes;
      } 
   
      void white_to_queue(int VFrom, int VTo, int depth)
      {
         if (queue.peek() == NULL && depth == 0)
         {
            queue.push(&vertex[VFrom], depth); // то помещаем в очередь
            vertex[VFrom].Hit = true;
            depth++; 
         }
         if(IsEdge(VFrom, VTo) == true)
         {
            stack.push(&vertex[VFrom], depth-1);
            stack.push(&vertex[VTo], depth);
            return;
         }
         else
         {
            for(int i = 0; i <= max_vertex; i++) // обход вершин
            {
               if (i == max_vertex && queue.peek() != NULL) // если записаны все связанные вершины
               { 
                  stack.push(queue.peek(), queue.depth()); // помещаем указатель на вершину в стек из очереди  
                  int depth_1 = stack.depth();      // глубина посл.вершины в стеке
                  queue.pop();
                  if (queue.peek() == NULL)
                     return;
                  int depth_2 = queue.depth();      // глубина след.вершины
                  if (depth_1 < depth_2)            // если глубина разная, то 
                     depth++;  
                  Vertex* v_from = queue.peek();    // смотрим след. элемент в очереди
                  white_to_queue( FindVertex(v_from->Value) , VTo, depth);  // делаем его вершиной 
               }
               else
               {  // если вершина существует, не посещена, и есть связь или это первый элемент
                  if((IsVertex(i) && vertex[i].Hit == false && IsEdge(VFrom, i))) 
                  {
                     queue.push(&vertex[i], depth); // то помещаем в очередь
                     vertex[i].Hit = true;
                  }   
               }
            }
         }
      }

      void white_to_stack(int VFrom, int VTo)
      {
         vertex[VFrom].Hit = true;   // Фиксируем вершину X как посещённую
         stack.push(&vertex[VFrom]); // Помещаем вершину X в стек
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
                  white_to_stack(i, VTo);     // то повторяем 
               if (stack.peek() == vertex + VTo)
                  return;
               if (i == max_vertex)
                  stack.pop(); //удаляем верхнюю вершину 
            }         
         }
      } 

      void clear_all_containers()
      {  while(queue.peek() != NULL) 
            queue.pop(); 
         while(stack.peek() != NULL) 
            stack.pop();
         for(int i = 0; i < max_vertex; i++) 
            vertex[i].Hit = false;         
      }
};
//=====================================================================================
/*
void print_way(Vertex** way)
{
   cout << endl; 
   if (way == NULL)
   {
      cout << "The way is not found" <<endl;
      return;
   }

   for(Vertex** i = way; *i != NULL; i++)   
   {
      Vertex* n = *i;
      cout << n->Value << endl;
   }
   cout << endl;
}

void print_table(SimpleGraph* Graph)
{
   cout << endl;  // проверка правильности создания таблицы  
   for(int i = 0; i < Graph->max_vertex; i++)   
   {
      for(int j = 0; j < Graph->max_vertex; j++)
      {
         cout << Graph->m_adjacency[i][j] << "  " ;
      }
      cout << endl;
   }   
}

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
   print_table(&Graph); // проверка правильности создания таблицы 
   cout << endl << "Test result: " << test << endl << endl;
   //=========================================
   SimpleGraph Graph2(6);
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
   print_table(&Graph2);
   print_way(way);
   //=========================================
   Graph2.AddEdge(3, 4);
   way = Graph2.BreadthFirstSearch(0, 3);   
   print_way(way);
   //=========================================
   Graph2.AddVertex(5);
   Graph2.AddEdge(4, 5);
   way = Graph2.BreadthFirstSearch(5, 0);
   print_way(way);
   //-----------------------------------------
   way = Graph2.BreadthFirstSearch(0, 5);
   print_way(way);
   //=========================================
   SimpleGraph Graph3(8); 
   Graph3.AddVertex(0);
   Graph3.AddVertex(1);
   Graph3.AddVertex(2);
   Graph3.AddVertex(3);
   Graph3.AddVertex(4);
   Graph3.AddVertex(5);
   Graph3.AddVertex(6);
   Graph3.AddVertex(7);
   Graph3.AddEdge(6, 2);
   Graph3.AddEdge(6, 3);
   Graph3.AddEdge(2, 3);
   Graph3.AddEdge(2, 1);
   Graph3.AddEdge(1, 4);
   Graph3.AddEdge(3, 4);
   Graph3.AddEdge(4, 7);
   Graph3.AddEdge(7, 5);
   print_table(&Graph3);

   way = Graph3.BreadthFirstSearch(6, 7);
   print_way(way);
   way = Graph3.BreadthFirstSearch(6, 0);
   print_way(way);
   //=====================================
   way = Graph3.WeakVertices();
   print_way(way);

}

void main()
{
   test();
   system("pause");
}
*/

