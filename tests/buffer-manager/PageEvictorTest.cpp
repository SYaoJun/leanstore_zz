#include "leanstore/buffer-manager/AsyncWriteBuffer.hpp"

#include "leanstore/buffer-manager/BufferFrame.hpp"
#include "leanstore/buffer-manager/Swip.hpp"
#include "leanstore/utils/Defer.hpp"
#include "leanstore/utils/Log.hpp"
#include "leanstore/utils/Misc.hpp"
#include "leanstore/utils/RandomGenerator.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>

#include <fcntl.h>

namespace leanstore::storage::test {

class AsyncWriteBufferTest : public ::testing::Test {
protected:
  std::string mTestDir = "/tmp/leanstore/AsyncWriteBufferTest";

  struct BufferFrameHolder {
    utils::AlignedBuffer<512> mBuffer;
    BufferFrame* mBf;

    BufferFrameHolder(size_t pageSize, PID pageId)
        : mBuffer(512 + pageSize),
          mBf(new(mBuffer.Get()) BufferFrame()) {
      mBf->mHeader.mPageId = pageId;
    }
  };

  void SetUp() override {
    // remove the test directory if it exists
    TearDown();

    // create the test directory
    auto ret = system(std::format("mkdir -p {}", mTestDir).c_str());
    EXPECT_EQ(ret, 0) << std::format(
        "Failed to create test directory, testDir={}, errno={}, error={}", mTestDir, errno,
        strerror(errno));
  }

  void TearDown() override {
  }

  std::string getRandTestFile() {
    return std::format("{}/{}", mTestDir, utils::RandomGenerator::RandAlphString(8));
  }

  int openFile(const std::string& fileName) {
    // open the file
    auto flag = O_TRUNC | O_CREAT | O_RDWR | O_DIRECT;
    int fd = open(fileName.c_str(), flag, 0666);
    EXPECT_NE(fd, -1) << std::format("Failed to open file, fileName={}, errno={}, error={}",
                                     fileName, errno, strerror(errno));

    return fd;
  }

  void closeFile(int fd) {
    ASSERT_EQ(close(fd), 0) << std::format("Failed to close file, fd={}, errno={}, error={}", fd,
                                           errno, strerror(errno));
  }

  void removeFile(const std::string& fileName) {
    ASSERT_EQ(remove(fileName.c_str()), 0) << std::format(
        "Failed to remove file, fileName={}, errno={}, error={}", fileName, errno, strerror(errno));
  }
};

TEST_F(PageEvictorTest, pageBasic) {
  PageEvictor pageEvictor;
}

} // namespace leanstore::storage::test