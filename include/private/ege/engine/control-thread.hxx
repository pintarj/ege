
#ifndef EGE_ENGINE_CONTROLTHREAD_HXX
#define EGE_ENGINE_CONTROLTHREAD_HXX

#include <chrono>
#include <memory>
#include <queue>
#include <ege/flow/executable.hxx>
#include <ege/flow/frame.hxx>
#include <ege/flow/scene.hxx>
#include <ege/flow/signal.hxx>
#include <ege/flow/thread.hxx>

namespace ege
{
    namespace engine
    {
        /**
         * \brief The thread that control the engine's execution.
         *
         * It requests frame rendering.
         * */
        class ControlThread: public flow::Thread
        {
            private:
                /**
                 * \brief Stores the current flow::Scene.
                 * */
                std::shared_ptr<flow::Scene> currentScene;

                /**
                 * \brief Stores the time point of the last time update.
                 * */
                flow::Frame::TimePoint lastFrameUpdate;

                /**
                 * \brief Contains the frame that is currently rendering/updating.
                 * */
                std::unique_ptr<flow::Frame> currentFrame;

                /**
                 * \brief Tells if the control thread is currently preparing graph execution.
                 * */
                bool preparingGraphExecution;

                /**
                 * \brief Mutex used to synchronize access to graph.
                 * */
                std::mutex graphPreparationMutex;

                /**
                 * \brief Signals the moment when the graph is prepared.
                 * */
                flow::Signal graphPreparedSignal;

                /**
                 * \brief Check if next scene is available, and eventually make it current.
                 * */
                void checkNextScene();

                /**
                 * \brief Requires next frame rendering that is updating a specified time.
                 * \param updateTime The time that the frame will represent (can also be future time).
                 * */
                void requireNextFrameRendering(flow::Frame::TimePoint updateTime = std::chrono::steady_clock::now());

            protected:
                /**
                 * \brief The control thread's execution body.
                 * */
                virtual void execute() override;

            public:
                /**
                 * \brief Create the control thread specifying the initial scene.
                 * \param initialScene The initial scene.
                 * */
                ControlThread(std::shared_ptr<flow::Scene> initialScene);

                virtual ~ControlThread();

                /**
                 * \brief Returns reference to current scene.
                 * \return Current scene.
                 * */
                flow::Scene& getCurrentScene() const noexcept;
        };
    }
}

#endif
