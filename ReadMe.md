109
234   slow fast 快慢指针的初始化slow := head  fast := head.Next  当fast!=nil&&fast.Next!=nil遍历时,奇数链表slow指向中间节点,偶数链表指向前半部分链表最后一个节点.好处是       都可以用slow.Next访问后半部分的第一个节点.根据fast为nil还是fast.Next为nil可判断slow是指向奇数链表的中间节点还是偶数链表的前半部分最后一个节点.
