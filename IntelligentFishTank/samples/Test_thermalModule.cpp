#include "thermalModule.h"
#include "threadPool.h"
#include "app.h"

#include <unistd.h>

int main() {
	App app;
	app.run();
	app.isRunning();
	while(true);
	return 0;
}