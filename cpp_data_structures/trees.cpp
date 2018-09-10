
struct Node
{
   int data;
   struct Node *next;
}

Node* InsertNth(Node *head, int data, int position)
{
  int i = 0;
  Node *temp = head;
  Node* newNode = new Node;
  newNode -> data = data;
  if(head==NULL){
      newNode -> next = NULL;
      return head;
  }
  while(temp!=NULL){
      if(i==0 && position==0) {
          newNode -> next = temp;
          return newNode;
      }
      else if(i==(position-1)) {
          newNode -> next = temp -> next;
          temp -> next = newNode;
          break;
      }
      else if(i>=position){
          temp -> next = newNode;
          break;
      }
      temp = temp->next;
      ++i;
  }
  return head;
}

Node* Delete(Node *head, int position)
{
  int i = 0;
  Node *n = head;
  if(i==position) {
      delete head;
      n = n -> next;
      return n;
  }
  while(n->next) {
      if((i+1)==position) {
          Node* temp = n->next->next;
          delete n->next;
          n->next = temp;
          return head;
      }
      ++i;
      n = n->next;
  }
  return head;
}