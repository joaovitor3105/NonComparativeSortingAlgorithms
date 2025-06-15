package Structures

type NodeStack struct {
    value int
    next  *NodeStack
}

type StackDynamic struct {
    top  *NodeStack
    size int
}

func NewStackDynamic() *StackDynamic {
    return &StackDynamic{
        top:  nil,
        size: 0,
    }
}

func (s *StackDynamic) Push(value int) {
    newNode := &NodeStack{
        value: value,
        next:  s.top,
    }
    s.top = newNode
    s.size++
}

func (s *StackDynamic) Pop() (int, bool) {
    if s.top == nil {
        return 0, false
    }
    
    value := s.top.value
    s.top = s.top.next
    s.size--
    return value, true
}

func (s *StackDynamic) ToArray() []int {
    result := make([]int, s.size)
    current := s.top
    
    for i := 0; i < s.size && current != nil; i++ {
        result[i] = current.value
        current = current.next
    }
    
    return result
}

func (s *StackDynamic) FromArray(arr []int) {
    s.top = nil
    s.size = 0
    
    for _, v := range arr {
        s.Push(v)
    }
}

func (s *StackDynamic) Size() int {
    return s.size
}