#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_dir(char* path);

int copy_file(char* srcPath, char* destPath);

int copy_folder(char* srcPath, char* destPath);

int is_dir(char* path) {
    struct stat st;
    stat(path, &st);
    if (S_ISDIR(st.st_mode))
        return 1;
    else
        return 0;
}

int copy_file(char* srcPath, char* destPath) {
    char Buf[1024] = {0};
    int count_read = 0;
    long fp_src_ltell = 0, fp_src_atell = 0;
    FILE* fp_src = fopen(srcPath, "r");
    FILE* fp_dst = fopen(destPath, "w");
    if (fp_dst == NULL || fp_src == NULL) {
        printf("文件打开有问题\n");
        return -1;
    }
    while (1) {
        memset(Buf, 0, sizeof(Buf));
        fp_src_ltell = ftell(fp_src);
        count_read = fread(Buf, sizeof(Buf), 1, fp_src);
        fp_src_atell = ftell(fp_src);
        if (count_read < 1) {
            if (feof(fp_src)) {
                long temp = fp_src_atell - fp_src_ltell;
                fwrite(Buf, temp, 1, fp_dst);
                return 0;
            } else if (ferror(fp_src)) {
                perror("fread error:");
                return -1;
            }
        }
        fwrite(Buf, sizeof(Buf), 1, fp_dst);
    }
    return 0;
}

int copy_folder(char* srcpath, char* destpath) {
    char newsrcpath[4096];
    char newdestpath[4096];
    if (mkdir(destpath, 0777)) {
        printf("文件复制成功.\n");
        return -1;
    }
    DIR* srcdp = opendir(srcpath);
    if (srcdp == NULL) {
        printf("打开文件夹[%s]失败！\n", srcpath);
        return -1;
    }
    struct dirent* srcdirent = NULL;
    int flag = 0;
    while (srcdirent = readdir(srcdp)) {
        flag++;
        if (flag > 0) {
            bzero(newsrcpath, sizeof(newsrcpath));
            bzero(newdestpath, sizeof(newdestpath));
            sprintf(newsrcpath, "%s/%s", srcpath, srcdirent->d_name);
            sprintf(newdestpath, "%s/%s", destpath, srcdirent->d_name);
            if (srcdirent->d_type == 4)
                copy_folder(newsrcpath, newdestpath);
            else
                copy_file(newsrcpath, newdestpath);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage srcfile destfile\n");
        return -1;
    }
    char* srcPath = argv[1];
    char* destPath = argv[2];
    if (is_dir(srcPath)) {
        copy_folder(srcPath, destPath);
    } else {
        if (access(destPath, F_OK) == 1) {
            printf("目标文件已存在\n");
            return -1;
        }
        copy_file(srcPath, destPath);
    }
    return 0;
}
