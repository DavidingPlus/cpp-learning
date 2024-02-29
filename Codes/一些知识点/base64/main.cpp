#include <iostream>
#include <string>
#include <string>
#include <fstream>
#include <unistd.h>

// 网上找到的一个算法，至少读取没有爆乱码
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(const char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const char *bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
            {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
        {
            ret += base64_chars[char_array_4[j]];
        }

        while ((i++ < 3))
        {
            ret += '=';
        }
    }

    return ret;
}

std::string base64_decode(std::string const &encoded_string)
{
    int in_len = (int)encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            ret += char_array_3[j];
    }

    return ret;
}

int main(int argc, char **argv)
{
    // 先删除拷贝文件
    if (0 == access("./LBJ_copy.jpg", F_OK))
        unlink("./LBJ_copy.jpg");

    std::cout << "Waiting to remove old copy files." << std::endl;
    sleep(1);

    std::fstream f;
    f.open("./LBJ.jpg", std::ios::in | std::ios::binary);
    f.seekg(0, std::ios_base::end); // 设置偏移量至文件结尾
    std::streampos sp = f.tellg();  // 获取文件大小
    int size = sp;

    char *buffer = (char *)malloc(sizeof(char) * size);
    f.seekg(0, std::ios_base::beg); // 设置偏移量至文件开头
    f.read(buffer, size);           // 将文件内容读入buffer
    std::cout << "file size:" << size << '\n'
              << std::endl;

    std::string imgBase64 = base64_encode(buffer, size); // 编码
    std::cout << "img base64 encode size: " << imgBase64.size() << std::endl;
    std::cout << "img base64 encode: " << imgBase64 << '\n'
              << std::endl;

    std::string imgdecode64 = base64_decode(imgBase64); // 解码
    std::cout << "img base64 decode size: " << imgdecode64.size() << std::endl;
    // std::cout << "img base64 decode: " << imgdecode64 << std::endl; // 乱码不打印

    const char *p = imgdecode64.c_str();
    std::ofstream fout("./LBJ_copy.jpg", std::ios::out | std::ios::binary);
    if (!fout)
    {
        std::cout << "error" << std::endl;
    }
    else
    {
        std::cout << "Success!" << std::endl;
        fout.write(p, size);
    }

    fout.close();

    return 0;
}
