/**\file */
#ifndef SLIC_DECLARATIONS_PearsonCoefficient_H
#define SLIC_DECLARATIONS_PearsonCoefficient_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] param_sample_size Interface Parameter "sample_size".
 * \param [in] ticks_PearsonCoefficientKernel The number of ticks for which kernel "PearsonCoefficientKernel" will run.
 * \param [in] instream_x0 Stream "x0".
 * \param [in] instream_size_x0 The size of the stream instream_x0 in bytes.
 * \param [in] instream_x1 Stream "x1".
 * \param [in] instream_size_x1 The size of the stream instream_x1 in bytes.
 * \param [out] outstream_y01 Stream "y01".
 * \param [in] outstream_size_y01 The size of the stream outstream_y01 in bytes.
 * \param [out] outstream_y11 Stream "y11".
 * \param [in] outstream_size_y11 The size of the stream outstream_y11 in bytes.
 */
void PearsonCoefficient(
	float param_sample_size,
	uint64_t ticks_PearsonCoefficientKernel,
	const void *instream_x0,
	size_t instream_size_x0,
	const void *instream_x1,
	size_t instream_size_x1,
	void *outstream_y01,
	size_t outstream_size_y01,
	void *outstream_y11,
	size_t outstream_size_y11);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_sample_size Interface Parameter "sample_size".
 * \param [in] ticks_PearsonCoefficientKernel The number of ticks for which kernel "PearsonCoefficientKernel" will run.
 * \param [in] instream_x0 Stream "x0".
 * \param [in] instream_size_x0 The size of the stream instream_x0 in bytes.
 * \param [in] instream_x1 Stream "x1".
 * \param [in] instream_size_x1 The size of the stream instream_x1 in bytes.
 * \param [out] outstream_y01 Stream "y01".
 * \param [in] outstream_size_y01 The size of the stream outstream_y01 in bytes.
 * \param [out] outstream_y11 Stream "y11".
 * \param [in] outstream_size_y11 The size of the stream outstream_y11 in bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *PearsonCoefficient_nonblock(
	float param_sample_size,
	uint64_t ticks_PearsonCoefficientKernel,
	const void *instream_x0,
	size_t instream_size_x0,
	const void *instream_x1,
	size_t instream_size_x1,
	void *outstream_y01,
	size_t outstream_size_y01,
	void *outstream_y11,
	size_t outstream_size_y11);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	float param_sample_size; /**<  [in] Interface Parameter "sample_size". */
	uint64_t ticks_PearsonCoefficientKernel; /**<  [in] The number of ticks for which kernel "PearsonCoefficientKernel" will run. */
	const void *instream_x0; /**<  [in] Stream "x0". */
	size_t instream_size_x0; /**<  [in] The size of the stream instream_x0 in bytes. */
	const void *instream_x1; /**<  [in] Stream "x1". */
	size_t instream_size_x1; /**<  [in] The size of the stream instream_x1 in bytes. */
	void *outstream_y01; /**<  [out] Stream "y01". */
	size_t outstream_size_y01; /**<  [in] The size of the stream outstream_y01 in bytes. */
	void *outstream_y11; /**<  [out] Stream "y11". */
	size_t outstream_size_y11; /**<  [in] The size of the stream outstream_y11 in bytes. */
} PearsonCoefficient_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void PearsonCoefficient_run(
	max_engine_t *engine,
	PearsonCoefficient_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *PearsonCoefficient_run_nonblock(
	max_engine_t *engine,
	PearsonCoefficient_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void PearsonCoefficient_run_group(max_group_t *group, PearsonCoefficient_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *PearsonCoefficient_run_group_nonblock(max_group_t *group, PearsonCoefficient_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void PearsonCoefficient_run_array(max_engarray_t *engarray, PearsonCoefficient_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *PearsonCoefficient_run_array_nonblock(max_engarray_t *engarray, PearsonCoefficient_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* PearsonCoefficient_convert(max_file_t *maxfile, PearsonCoefficient_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* PearsonCoefficient_init(void);

/* Error handling functions */
int PearsonCoefficient_has_errors(void);
const char* PearsonCoefficient_get_errors(void);
void PearsonCoefficient_clear_errors(void);
/* Free statically allocated maxfile data */
void PearsonCoefficient_free(void);
/* These are dummy functions for hardware builds. */
int PearsonCoefficient_simulator_start(void);
int PearsonCoefficient_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_PearsonCoefficient_H */

