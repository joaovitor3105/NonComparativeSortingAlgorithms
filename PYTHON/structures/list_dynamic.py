# structures/list_dynamic.py
from typing import List, Optional
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class NodeList:
    """Nó para lista encadeada"""
    def __init__(self, value: int):
        self.value = value
        self.next: Optional['NodeList'] = None


class ListDynamic(DataStructure):
    """Lista com alocação dinâmica (lista encadeada)"""
    
    def __init__(self):
        self.head: Optional[NodeList] = None
        self.tail: Optional[NodeList] = None  # Otimização O(1) para inserção
        self._size = 0
    
    def add(self, value: int) -> None:
        new_node = NodeList(value)
        
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        
        self._size += 1
    
    def to_array(self) -> List[int]:
        result = []
        current = self.head
        
        while current is not None:
            result.append(current.value)
            current = current.next
        
        return result
    
    def from_array(self, arr: List[int]) -> None:
        self.head = None
        self.tail = None
        self._size = 0
        
        for v in arr:
            self.add(v)
    
    def size(self) -> int:
        return self._size