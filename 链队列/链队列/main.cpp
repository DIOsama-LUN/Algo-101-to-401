#include "LinkQueue.h"
#include <stdio.h>

/**
 * @brief 用户输入入队（支持连续输入多个字符，按回车结束）
 * @param Q 队列指针（需传入已定义的队列地址）
 */
void InputEnQueue(LinkQueue* Q) {
    char input;
    printf("=== 入队操作（用户输入）===\n");
    printf("请输入要入队的字符（可连续输入多个，按【回车】结束）：\n");

    // 循环读取用户输入，直到按下回车
    while ((input = getchar()) != '\n') {
        // 过滤空格（可选，不想过滤可删除此判断）
        if (input == ' ') {
            continue;
        }

        // 调用入队函数，每个有效字符依次入队
        if (enQueue(Q, input) == OK) {
            printf("字符 '%c' 入队成功！\n", input);
        }
        else {
            printf("字符 '%c' 入队失败！\n", input);
        }
    }
}

/**
 * @brief 出队操作（取出队首第一个元素，演示核心流程）
 * @param Q 队列指针
 */
void DeQueueOnce(LinkQueue* Q) {
    char e;
    printf("\n=== 出队操作 ===\n");

    // 出队前先判空（避免无效操作）
    if (QueueEmpty(Q) == TRUE) {
        printf("队列为空，无法出队！\n");
        return;
    }

    // 执行单次出队（仅取出队首第一个元素）
    if (deQueue(*Q, &e) == OK) {
        printf("出队成功！出队元素：'%c'\n", e);
    }
    else {
        printf("出队失败！\n");
    }
}

int main() {
    LinkQueue Q; // 定义队列变量（非指针，避免野指针问题）

    // 1. 初始化队列
    printf("=== 初始化队列 ===\n");
    if (InitQueue(&Q) != OK) { // 传队列地址（符合函数参数LinkQueue* Q）
        printf("队列初始化失败，程序退出！\n");
        return 1;
    }

    // 2. 用户输入入队
    InputEnQueue(&Q);

    // 3. 第一次判空（预期：非空）
    printf("\n=== 第一次判空（入队后）===\n");
    if (QueueEmpty(&Q) == TRUE) {
        printf("结果：队列为空\n");
    }
    else {
        printf("结果：队列非空（符合预期）\n");
    }

    // 4. 执行出队（取出队首第一个元素）
    DeQueueOnce(&Q);

    // 5. 第二次判空（可能空/非空，取决于入队元素数量）
    printf("\n=== 第二次判空（出队后）===\n");
    if (QueueEmpty(&Q) == TRUE) {
        printf("结果：队列为空\n");
    }
    else {
        printf("结果：队列非空（仍有剩余元素）\n");
    }

    // 6. 销毁队列（释放所有内存）
    printf("\n=== 销毁队列 ===\n");
    DestroyQueue(&Q); // 传队列地址
    printf("队列销毁完成！\n");
    system("pause");
    return 0;
}