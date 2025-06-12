package Structures

type NodeList struct {
    value int
    next  *NodeList
}

type ListDynamic struct {
    head *NodeList
    size int
}

func NewListDynamic() *ListDynamic {
    return &ListDynamic{
        head: nil,
        size: 0,
    }
}

func (l *ListDynamic) Add(value int) {
    newNode := &NodeList{value: value, next: nil}
    
    if l.head == nil {
        l.head = newNode
    } else {
        current := l.head
        for current.next != nil {
            current = current.next
        }
        current.next = newNode
    }
    l.size++
}

func (l *ListDynamic) ToArray() []int {
    result := make([]int, l.size)
    current := l.head
    i := 0
    
    for current != nil {
        result[i] = current.value
        current = current.next
        i++
    }
    
    return result
}

func (l *ListDynamic) FromArray(arr []int) {
    l.head = nil
    l.size = 0
    
    for _, v := range arr {
        l.Add(v)
    }
}

func (l *ListDynamic) Size() int {
    return l.size
}