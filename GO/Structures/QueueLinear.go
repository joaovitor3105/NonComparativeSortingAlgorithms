package Structures

type QueueLinear struct {
    data     []int
    front    int
    rear     int
    size     int
    capacity int
}

func NewQueueLinear(capacity int) *QueueLinear {
    return &QueueLinear{
        data:     make([]int, capacity),
        front:    0,
        rear:     -1,
        size:     0,
        capacity: capacity,
    }
}

func (q *QueueLinear) Enqueue(value int) {
    if q.size < q.capacity {
        q.rear = (q.rear + 1) % q.capacity
        q.data[q.rear] = value
        q.size++
    }
}

func (q *QueueLinear) Dequeue() (int, bool) {
    if q.size == 0 {
        return 0, false
    }
    
    value := q.data[q.front]
    q.front = (q.front + 1) % q.capacity
    q.size--
    return value, true
}

func (q *QueueLinear) ToArray() []int {
    result := make([]int, q.size)
    for i := 0; i < q.size; i++ {
        index := (q.front + i) % q.capacity
        result[i] = q.data[index]
    }
    return result
}

func (q *QueueLinear) FromArray(arr []int) {
    q.front = 0
    q.rear = -1
    q.size = 0
    
    for _, v := range arr {
        q.Enqueue(v)
    }
}

func (q *QueueLinear) Size() int {
    return q.size
}