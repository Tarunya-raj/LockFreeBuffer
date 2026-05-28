ZERO COPY LOCK FREE RING BUFFER IPC FRAMEWORK

(Shared memory based approach to shared the data between two process, without having to copying it in User's buffer 
then Kernel's buffer, to reduce the overhead during context switching)

LockFreeIPC/
├── 3rdParty/          # External dependencies (e.g., Google Test, Benchmark)
├── common/            # Shared utilities, helper classes, macros
├── examples/          # POCs, standalone projects (e.g. cicular/ring buffer,multi-threaded queue using mutex,  shm_client, shm_server)
├── include/           # Public/API header files
│   └── project_name/  # namespace, headers
├── src/               # Core source files (.cpp) and private headers
├── test/              # Unit tests, functional tests, integration tests
├── build/             # Recommended: Avoid cluttering root with builds
│   ├── debug/         # Artifacts for Debug Build
│   └── release/       # Artifacts for Release Build
├── Makefile           # Build automation
└── readme.md          # Documentation


Phase 1 — Ring Buffer Basics (3–5 days)

	Learn:
		circular queue
		head/tail logic
		overwrite/full conditions

	Implement:

	single-threaded ring buffer
	(NOTE: ) explicit bounds checking and modulo math 
	(or better yet, keep your buffer size a power of 2 
	so you can use bitwise & (SIZE - 1) instead of the costly % modulo operator)

Phase 2 — Thread-Safe Version (1–2 weeks)

	Learn:
		mutex
		condition_variable
		producer-consumer pattern
		Debugging helgrind (valgrind tool)

	Implement:
	single-threaded queue using mutex
	*multiple-threaded queue using mutex (ThreadSanitizer validation)

DEMO: Present a working mutex-based single-producer/consumer queue with no data loss under load.

Phase 3 — Atomics & Lock-Free (3-4 weeks)

	Learn deeply:

	std::atomic
	memory ordering
	Cache-Line Padding -Measure False sharing 
	Especially:

	memory_order_relaxed
	memory_order_acquire
	memory_order_release

	Then implement:
	SPSC lock-free queue
	Single Producer
	Single Consumer

Phase 4 — Shared Memory IPC (1–2 weeks)

	Learn:
	mmap, shm_open, ftok- shared memory key generation
	shared memory regions
	placement new

	Then:move your ring buffer into shared memory, Now two processes communicate.



Phase 5 — Zero-Copy Design (1 week)

	Instead of copying payloads:

	share memory blocks
	pass indexes/offsets

DEMO: Showcase two processes exchanging messages via shared memory.

Phase 6 — Framework/API Layer (1–2 weeks)

	Build:

	clean API
	error handling
	benchmarks
	logging
	tests

 DEMO: Bug fixes, integration, What if producer crashes mid-write? 

 Phase 7: Deployment - (1-2 week)

		Crash recovery (magic numbers, versioning, stale process detection)
		ABA problem solution + cache-line padding + ThreadSanitizer validation
		Bug Fixes

Core Features

	Shared memory communication
	Ring buffer
	Lock-free SPSC queue
	Fixed-size messages
	Zero-copy reads/writes
	Benchmarking
	Clean API
	Linux support