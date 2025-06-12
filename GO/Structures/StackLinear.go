package Structures

type StackLinear struct {
    data     []int
    top      int
    capacity int
}

func NewStackLinear(capacity int) *StackLinear {
    return &StackLinear{
        data:     make([]int, capacity),
        top:      -1,
        capacity: capacity,
    }
}

func (s *StackLinear) Push(value int) {
    if s.top < s.capacity-1 {
        s.top++
        s.data[s.top] = value
    }
}

func (s *StackLinear) Pop() (int, bool) {
    if s.top == -1 {
        return 0, false
    }
    
    value := s.data[s.top]
    s.top--
    return value, true
}

func (s *StackLinear) ToArray() []int {
    result := make([]int, s.top+1)
    copy(result, s.data[:s.top+1])
    return result
}

func (s *StackLinear) FromArray(arr []int) {
    s.top = -1
    for _, v := range arr {
        s.Push(v)
    }
}

func (s *StackLinear) Size() int {
    return s.top + 1
}