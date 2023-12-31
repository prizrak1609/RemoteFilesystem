#pragma once

#include <QObject>
#include <QFuture>
#include <QThread>
#include <QDir>
#include <fuse3/fuse.h>

class Filesystem : public QThread
{
    Q_OBJECT

    friend struct FileSystemImpl;
public:
    using ptr = std::unique_ptr<Filesystem>;

    ~Filesystem();

    static Filesystem::ptr& get_instance();

    QString cache_folder;
    QString mount_path;

signals:
    void error(QString);

private:
    static ptr instance;
    fuse_statvfs filesystem_stat;
    QDir cache;
    QMap<QString, QString> file_attributes;

    struct OpenedFile
    {
        QMutex* mutex = new QMutex();
        int links = 1;
    };

    QMap<QString, OpenedFile> opened_files;

    Filesystem(QObject *parent = nullptr);

    void* init(fuse3_conn_info *conn, fuse3_config *conf);
    int get_attr(const char *path, struct fuse_stat *stbuf, struct fuse3_file_info *fi);
    int read_dir(const char *path, void *buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info *fi, enum fuse3_readdir_flags flags);
    int mkdir(const char *path, fuse_mode_t mode);
    int rmdir(const char *path);
    int rename(const char *oldpath, const char *newpath, unsigned int flags);
    int create_file(const char *path, fuse_mode_t mode, struct fuse3_file_info *fi);
    int remove_file(const char *path);
    int open_file(const char *path, struct fuse3_file_info *fi);
    int read_file(const char *path, char *buf, size_t size, fuse_off_t off, struct fuse3_file_info *fi);
    int write_file(const char *path, const char *buf, size_t size, fuse_off_t off, struct fuse3_file_info *fi);
    int close_file(const char *path, struct fuse3_file_info *fi);
    int stat_fs(const char *path, struct fuse_statvfs *stbuf);

    void destroy(void* data);
    QString cache_path(const char *path);
    void convert_to_stat(QString doc, struct fuse_stat *stbuf);

    // QThread interface
protected:
    void run() override;
};
