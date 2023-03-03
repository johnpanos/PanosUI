#include <memory>
#include <stdio.h>
#include <unistd.h>

#include <inttypes.h>
#include <sys/socket.h>
#include <sys/types.h>

struct ViewRect
{
	int x, y;
};

class ViewImpl
{
  public:
	ViewImpl()
	{
	}

	void SetFrame()
	{
	}

	const ViewRect &frame() const
	{
	}
};

struct Header
{
	uint32_t payload_size;
};

struct MyStruct
{
	struct Header header;
	int my_value;
};

void parent(int socket)
{
	auto view = std::make_unique<ViewImpl>();

	view->SetFrame();
	view->frame();

	struct MyStruct myStructImpl;
	myStructImpl.header.payload_size = sizeof(int);
	myStructImpl.my_value = 100;
	write(socket, &myStructImpl, sizeof(myStructImpl));
}

void child(int socket)
{
	struct Header header;
	int n = read(socket, &header, sizeof(struct Header));

	int my_value;
	read(socket, &my_value, sizeof(header.payload_size));

	printf("parent received '%d': %d\n", header.payload_size, my_value);
}

int main()
{
	int fd[2], len;

	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, fd) == -1)
	{
		return 1;
	}

	// Parent
	if (fork())
	{
		close(fd[1]);
		parent(fd[0]);
	}
	// Child
	else
	{
		close(fd[0]);
		child(fd[1]);
	}
}