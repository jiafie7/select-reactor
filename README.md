# select-reactor

I combined the [select-based socket processing framework](https://github.com/jiafie7/select) with the [C++ thread pool framework](https://github.com/jiafie7/posix-thread) to implement the select-based Reactor model.

## 🖥️ Getting Started

1. Clone the Repository

```sh
git clone https://github.com/jiafie7/select-reactor.git
cd select-reactor
```

2. Build the Project

```sh
mkdir build && cd build
cmake ..
make

./server &

./client
```

## 📝 License

This project is licensed under the MIT License. See the LICENSE file for more information.

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome. Feel free to fork the repository, open issues, or submit pull requests.
