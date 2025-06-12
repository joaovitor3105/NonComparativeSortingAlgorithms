package Structures

type NodeQueue struct {
    value int
    next  *NodeQueue
}

type QueueDynamic struct {
    front *NodeQueue
    rear  *NodeQueue
    size  int
}

func NewQueueDynamic() *QueueDynamic {
    return &QueueDynamic{
        front: nil,
        rear:  nil,
        size:  0,
    }
}

func (q *QueueDynamic) Enqueue(value int) {
    newNode := &NodeQueue{value: value, next: nil}
    
    if q.rear == nil {
        q.front = newNode
        q.rear = newNode
    } else {
        q.rear.next = newNode
        q.rear = newNode
    }
    q.size++
}

func (q *QueueDynamic) Dequeue() (int, bool) {
    if q.front == nil {
        return 0, false
    }
    
    value := q.front.value
    q.front = q.front.next
    
    if q.front == nil {
        q.rear = nil
    }
    
    q.size--
    return value, true
}

func (q *QueueDynamic) ToArray() []int {
    result := make([]int, q.size)
    current := q.front
    i := 0
    
    for current != nil {
        result[i] = current.value
        current = current.next
        i++
    }
    
    return result
}

func (q *QueueDynamic) FromArray(arr []int) {
    q.front = nil
    q.rear = nil
    q.size = 0
    
    for _, v := range arr {
        q.Enqueue(v)
    }
}

func (q *QueueDynamic) Size() int {
    return q.size
}