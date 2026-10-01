#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capa): capacity(capa) {}

size_t ByteStream::write(const string &data) { // 将 data 中尽可能多的字节写入 stream，返回实际写入的字节数
    if (is_end) {
        return 0;
    }
    const size_t cnt = std::min(data.size(), remaining_capacity());
    for (size_t i = 0; i < cnt; ++i) {
        str_buf.push_back(data[i]);
    }
    written_bytes += cnt;
    return cnt;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const { // 返回接下来至多 len 个字节，但不移除它们
    const size_t cnt = std::min(len, str_buf.size());
    std::string res;
    res.resize(cnt);
    for (size_t i = 0; i < cnt; i++) {
        res[i] = str_buf[i];
    }
    return res;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    const size_t cnt = std::min(len, str_buf.size());
    for (size_t i = 0; i < cnt; i++) {
        str_buf.pop_front();
    }
    read_bytes += cnt;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string res = peek_output(len);
    pop_output(res.size());
    return res;
}

void ByteStream::end_input() {
    is_end = true;
}

bool ByteStream::input_ended() const { return is_end; }

size_t ByteStream::buffer_size() const { return str_buf.size(); }

bool ByteStream::buffer_empty() const { return str_buf.size() == 0; }

bool ByteStream::eof() const { return is_end && str_buf.empty(); }

size_t ByteStream::bytes_written() const { return written_bytes; }

size_t ByteStream::bytes_read() const { return read_bytes; }

size_t ByteStream::remaining_capacity() const { return capacity - str_buf.size(); }
