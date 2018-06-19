void DK_NVIC_Init(u8 Group);//设置优先级分组
//中断向量，抢占优先级，子优先级0，使能还是不使能
void DK_NVIC_IRQ_Set(u8 NVIC_IRQChannel, u8 pre_pri, u8 sub_pri, FunctionalState cmd);
//设置外部中断6，下降沿，PB6
//DK_NVIC_Init(4);//选择NVIC_PriorityGroup_4，4位全部为占先式优先级，要实现中断必须先初始化NVIC
//DK_NVIC_IRQ_Set(EXTI9_5_IRQn,0,0,ENABLE); //抢先优先级0
