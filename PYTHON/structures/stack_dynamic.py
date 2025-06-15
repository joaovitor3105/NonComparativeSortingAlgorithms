# structures/stack_dynamic.py
from typing import List, Optional, Tuple
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class NodeStack:
    """Nó para pilha encadeada"""
    def __init__(self, value: int):
        self.value = value
        self.next: Optional['NodeStack'] = None


class StackDynamic(DataStructure):
    """Pilha com alocação dinâmica (lista encadeada)"""
    
    def __init__(self):
        self.top: Optional[NodeStack] = None
        self._size = 0
    
    def push(self, value: int) -> None:
        new_node = NodeStack(value)
        new_node.next = self.top
        self.top = new_node
        self._size += 1
    
    def pop(self) -> Tuple[int, bool]:
        if self.top is None:
            return 0, False
        
        value = self.top.value
        self.top = self.top.next
        self._size -= 1
        return value, True
    
    def to_array(self) -> List[int]:
        result = []
        current = self.top
        
        while current is not None:
            result.append(current.value)
            current = current.next
        
        return result
    
    def from_array(self, arr: List[int]) -> None:
        self.top = None
        self._size = 0
        
        for v in arr:
            self.push(v)
    
    def size(self) -> int:
        return self._size