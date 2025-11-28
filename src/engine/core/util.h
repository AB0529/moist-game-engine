#pragma once

static inline void _remove_item(void** array, int* count, void* item) {
	int found = -1;
	for (int i = 0; i < *count; i++) {
		if (array[i] == item) {
			found = i;
			break;
		}
	}

	if (found == -1)
		return;

	for (int i = found; i < *count - 1; i++) {
		array[i] = array[i + 1];
	}
	(*count)--;
}
