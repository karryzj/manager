#ifndef PDK_INFO_H
#define PDK_INFO_H

#include <QString>

typedef struct
{
    int border_line;
    int border_color;
    int fill_line;
    int fill_color;
} BorderStyle;

typedef struct
{
    QString layer_name;
    int gds_number;
    int data_type;
    BorderStyle style;
} PdkInfo;

// 重载 == 运算符，用于比较两个 PdkInfo 结构体是否相等
inline bool operator==(const PdkInfo &lhs, const PdkInfo &rhs)
{
    return lhs.layer_name == rhs.layer_name &&
           lhs.gds_number == rhs.gds_number &&
           lhs.data_type == rhs.data_type;
}

inline bool operator!=(const PdkInfo &lhs, const PdkInfo &rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(const BorderStyle &lhs, const BorderStyle &rhs)
{
    return lhs.border_line == rhs.border_line &&
           lhs.border_color == rhs.border_color &&
           lhs.fill_line == rhs.fill_line &&
           lhs.fill_color == rhs.fill_color;
}

inline bool operator!=(const BorderStyle &lhs, const BorderStyle &rhs)
{
    return !(lhs == rhs);
}

#endif // PDK_INFO_H
