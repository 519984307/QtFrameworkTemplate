#include "common_util.h"
#ifdef __APPLE__
#include "Feedback/FeedbackInfo.h"
#endif


#ifdef __APPLE__
void sendMacFeedbackInfo(const QString& info){
    FeedbackInfo feedback;
    feedback.SendFeedback(info);
}
#endif
