/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#include "Auth/AWSCoreCredentials.h"
#include "Client/AWSClientConfiguration.h"

#include "GameLiftError.h"

#include "Model/AcceptMatchRequest.h"
#include "Model/GameLiftCreateAliasRequest.h"
#include "Model/CreateBuildRequest.h"
#include "Model/CreateFleetRequest.h"
#include "Model/CreateGameSessionRequest.h"
#include "Model/CreateGameSessionQueueRequest.h"
#include "Model/CreateMatchmakingConfigurationRequest.h"
#include "Model/CreateMatchmakingRuleSetRequest.h"
#include "Model/CreatePlayerSessionRequest.h"
#include "Model/CreatePlayerSessionsRequest.h"
#include "Model/CreateScriptRequest.h"
#include "Model/CreateVpcPeeringAuthorizationRequest.h"
#include "Model/CreateVpcPeeringConnectionRequest.h"
#include "Model/GameLiftDeleteAliasRequest.h"
#include "Model/DeleteBuildRequest.h"
#include "Model/DeleteFleetRequest.h"
#include "Model/DeleteGameSessionQueueRequest.h"
#include "Model/DeleteMatchmakingConfigurationRequest.h"
#include "Model/DeleteMatchmakingRuleSetRequest.h"
#include "Model/DeleteScalingPolicyRequest.h"
#include "Model/DeleteScriptRequest.h"
#include "Model/DeleteVpcPeeringAuthorizationRequest.h"
#include "Model/DeleteVpcPeeringConnectionRequest.h"
#include "Model/DescribeAliasRequest.h"
#include "Model/DescribeBuildRequest.h"
#include "Model/DescribeEC2InstanceLimitsRequest.h"
#include "Model/DescribeFleetAttributesRequest.h"
#include "Model/DescribeFleetCapacityRequest.h"
#include "Model/DescribeFleetEventsRequest.h"
#include "Model/DescribeFleetPortSettingsRequest.h"
#include "Model/DescribeFleetUtilizationRequest.h"
#include "Model/DescribeGameSessionDetailsRequest.h"
#include "Model/DescribeGameSessionPlacementRequest.h"
#include "Model/DescribeGameSessionQueuesRequest.h"
#include "Model/DescribeGameSessionsRequest.h"
#include "Model/DescribeInstancesRequest.h"
#include "Model/DescribeMatchmakingRequest.h"
#include "Model/DescribeMatchmakingConfigurationsRequest.h"
#include "Model/DescribeMatchmakingRuleSetsRequest.h"
#include "Model/DescribePlayerSessionsRequest.h"
#include "Model/DescribeRuntimeConfigurationRequest.h"
#include "Model/DescribeScalingPoliciesRequest.h"
#include "Model/DescribeScriptRequest.h"
#include "Model/DescribeVpcPeeringAuthorizationsRequest.h"
#include "Model/DescribeVpcPeeringConnectionsRequest.h"
#include "Model/GetGameSessionLogUrlRequest.h"
#include "Model/GetInstanceAccessRequest.h"
#include "Model/GameLiftListAliasesRequest.h"
#include "Model/ListBuildsRequest.h"
#include "Model/ListFleetsRequest.h"
#include "Model/ListScriptsRequest.h"
#include "Model/PutScalingPolicyRequest.h"
#include "Model/RequestUploadCredentialsRequest.h"
#include "Model/ResolveAliasRequest.h"
#include "Model/SearchGameSessionsRequest.h"
#include "Model/StartFleetActionsRequest.h"
#include "Model/StartGameSessionPlacementRequest.h"
#include "Model/StartMatchBackfillRequest.h"
#include "Model/StartMatchmakingRequest.h"
#include "Model/StopFleetActionsRequest.h"
#include "Model/StopGameSessionPlacementRequest.h"
#include "Model/StopMatchmakingRequest.h"
#include "Model/GameLiftUpdateAliasRequest.h"
#include "Model/UpdateBuildRequest.h"
#include "Model/UpdateFleetAttributesRequest.h"
#include "Model/UpdateFleetCapacityRequest.h"
#include "Model/UpdateFleetPortSettingsRequest.h"
#include "Model/UpdateGameSessionRequest.h"
#include "Model/UpdateGameSessionQueueRequest.h"
#include "Model/UpdateMatchmakingConfigurationRequest.h"
#include "Model/UpdateRuntimeConfigurationRequest.h"
#include "Model/UpdateScriptRequest.h"
#include "Model/ValidateMatchmakingRuleSetRequest.h"

#include "Model/AcceptMatchResult.h"
#include "Model/GameLiftCreateAliasResult.h"
#include "Model/CreateBuildResult.h"
#include "Model/CreateFleetResult.h"
#include "Model/CreateGameSessionResult.h"
#include "Model/CreateGameSessionQueueResult.h"
#include "Model/CreateMatchmakingConfigurationResult.h"
#include "Model/CreateMatchmakingRuleSetResult.h"
#include "Model/CreatePlayerSessionResult.h"
#include "Model/CreatePlayerSessionsResult.h"
#include "Model/CreateScriptResult.h"
#include "Model/CreateVpcPeeringAuthorizationResult.h"
#include "Model/CreateVpcPeeringConnectionResult.h"
#include "Model/DeleteGameSessionQueueResult.h"
#include "Model/DeleteMatchmakingConfigurationResult.h"
#include "Model/DeleteMatchmakingRuleSetResult.h"
#include "Model/DeleteVpcPeeringAuthorizationResult.h"
#include "Model/DeleteVpcPeeringConnectionResult.h"
#include "Model/DescribeAliasResult.h"
#include "Model/DescribeBuildResult.h"
#include "Model/DescribeEC2InstanceLimitsResult.h"
#include "Model/DescribeFleetAttributesResult.h"
#include "Model/DescribeFleetCapacityResult.h"
#include "Model/DescribeFleetEventsResult.h"
#include "Model/DescribeFleetPortSettingsResult.h"
#include "Model/DescribeFleetUtilizationResult.h"
#include "Model/DescribeGameSessionDetailsResult.h"
#include "Model/DescribeGameSessionPlacementResult.h"
#include "Model/DescribeGameSessionQueuesResult.h"
#include "Model/DescribeGameSessionsResult.h"
#include "Model/DescribeInstancesResult.h"
#include "Model/DescribeMatchmakingResult.h"
#include "Model/DescribeMatchmakingConfigurationsResult.h"
#include "Model/DescribeMatchmakingRuleSetsResult.h"
#include "Model/DescribePlayerSessionsResult.h"
#include "Model/DescribeRuntimeConfigurationResult.h"
#include "Model/DescribeScalingPoliciesResult.h"
#include "Model/DescribeScriptResult.h"
#include "Model/DescribeVpcPeeringAuthorizationsResult.h"
#include "Model/DescribeVpcPeeringConnectionsResult.h"
#include "Model/GetGameSessionLogUrlResult.h"
#include "Model/GetInstanceAccessResult.h"
#include "Model/GameLiftListAliasesResult.h"
#include "Model/ListBuildsResult.h"
#include "Model/ListFleetsResult.h"
#include "Model/ListScriptsResult.h"
#include "Model/PutScalingPolicyResult.h"
#include "Model/RequestUploadCredentialsResult.h"
#include "Model/ResolveAliasResult.h"
#include "Model/SearchGameSessionsResult.h"
#include "Model/StartFleetActionsResult.h"
#include "Model/StartGameSessionPlacementResult.h"
#include "Model/StartMatchBackfillResult.h"
#include "Model/StartMatchmakingResult.h"
#include "Model/StopFleetActionsResult.h"
#include "Model/StopGameSessionPlacementResult.h"
#include "Model/StopMatchmakingResult.h"
#include "Model/GameLiftUpdateAliasResult.h"
#include "Model/UpdateBuildResult.h"
#include "Model/UpdateFleetAttributesResult.h"
#include "Model/UpdateFleetCapacityResult.h"
#include "Model/UpdateFleetPortSettingsResult.h"
#include "Model/UpdateGameSessionResult.h"
#include "Model/UpdateGameSessionQueueResult.h"
#include "Model/UpdateMatchmakingConfigurationResult.h"
#include "Model/UpdateRuntimeConfigurationResult.h"
#include "Model/UpdateScriptResult.h"
#include "Model/ValidateMatchmakingRuleSetResult.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/GameLiftClient.h"

#endif

#include "GameLiftClientObject.generated.h"

/**
*  <fullname>Amazon GameLift Service</fullname> <p> Amazon GameLift is a managed service for developers who need a scalable, dedicated server solution for their multiplayer games. Use Amazon GameLift for these tasks: (1) set up computing resources and deploy your game servers, (2) run game sessions and get players into games, (3) automatically scale your resources to meet player demand and manage costs, and (4) track in-depth metrics on game server performance and player usage.</p> <p>When setting up hosting resources, you can deploy your custom game server or use the Amazon GameLift Realtime Servers. Realtime Servers gives you the ability to quickly stand up lightweight, efficient game servers with the core Amazon GameLift infrastructure already built in.</p> <p> <b>Get Amazon GameLift Tools and Resources</b> </p> <p>This reference guide describes the low-level service API for Amazon GameLift and provides links to language-specific SDK reference topics. See also <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-components.html"> Amazon GameLift Tools and Resources</a>.</p> <p> <b>API Summary</b> </p> <p>The Amazon GameLift service API includes two key sets of actions:</p> <ul> <li> <p>Manage game sessions and player access -- Integrate this functionality into game client services in order to create new game sessions, retrieve information on existing game sessions; reserve a player slot in a game session, request matchmaking, etc.</p> </li> <li> <p>Configure and manage game server resources -- Manage your Amazon GameLift hosting resources, including builds, scripts, fleets, queues, and aliases. Set up matchmakers, configure auto-scaling, retrieve game logs, and get hosting and game metrics.</p> </li> </ul> <p> <b> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/reference-awssdk.html"> Task-based list of API actions</a> </b> </p>
**/
UCLASS(BlueprintType)
class GAMELIFT_API UGameLiftClientObject : public UObject {
    GENERATED_BODY()

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    Aws::GameLift::GameLiftClient *awsGameLiftClient;
#endif

public:
    /**
    * public static UGameLiftClientObject::CreateGameLiftObject
    * Creates a GameLiftClientObject. This function must be called first before accessing any GameLift client functions.
    * @param credentials [FAWSCredentials] .
    * @param clientConfiguration [FClientConfiguration] .
    * @return [UGameLiftClient*] Returns UGameLiftClient*.
    **/
    UFUNCTION(BlueprintCallable, Category = "GameLift Client")
    static UGameLiftClientObject *
    CreateGameLiftObject(const FAWSCredentials &credentials, const FAWSClientConfiguration &clientConfiguration);

    /**
    * public const UGameLiftClient::GetGameLiftClientName
    * @return [FString] Returns .
    **/
    UFUNCTION(BlueprintCallable, Category = "GameLift Client")
    FString
    GetServiceClientName() const;

    /**
    *  <p>Registers a player's acceptance or rejection of a proposed FlexMatch match. A matchmaking configuration may require player acceptance; if so, then matches built with that configuration cannot be completed unless all players accept the proposed match within a specified time limit. </p> <p>When FlexMatch builds a match, all the matchmaking tickets involved in the proposed match are placed into status <code>REQUIRES_ACCEPTANCE</code>. This is a trigger for your game to get acceptance from all players in the ticket. Acceptances are only valid for tickets when they are in this status; all other acceptances result in an error.</p> <p>To register acceptance, specify the ticket ID, a response, and one or more players. Once all players have registered acceptance, the matchmaking tickets advance to status <code>PLACING</code>, where a new game session is created for the match. </p> <p>If any player rejects the match, or if acceptances are not received before a specified timeout, the proposed match is dropped. The matchmaking tickets are then handled in one of two ways: For tickets where one or more players rejected the match, the ticket status is returned to <code>SEARCHING</code> to find a new match. For tickets where one or more players failed to respond, the ticket status is set to <code>CANCELLED</code>, and processing is terminated. A new matchmaking request for these players can be submitted as needed. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-client.html"> Add FlexMatch to a Game Client</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-events.html"> FlexMatch Events Reference</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>StartMatchmaking</a> </p> </li> <li> <p> <a>DescribeMatchmaking</a> </p> </li> <li> <p> <a>StopMatchmaking</a> </p> </li> <li> <p> <a>AcceptMatch</a> </p> </li> <li> <p> <a>StartMatchBackfill</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/AcceptMatch">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param acceptMatchRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void AcceptMatch (
        UObject *WorldContextObject,
        bool &success,
        FAcceptMatchRequest acceptMatchRequest,
        FAcceptMatchResult &acceptMatchResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates an alias for a fleet. In most situations, you can use an alias ID in place of a fleet ID. By using a fleet alias instead of a specific fleet ID, you can switch gameplay and players to a new fleet without changing your game client or other game components. For example, for games in production, using an alias allows you to seamlessly redirect your player base to a new game server update. </p> <p>Amazon GameLift supports two types of routing strategies for aliases: simple and terminal. A simple alias points to an active fleet. A terminal alias is used to display messaging or link to a URL instead of routing players to an active fleet. For example, you might use a terminal alias when a game version is no longer supported and you want to direct players to an upgrade site. </p> <p>To create a fleet alias, specify an alias name, routing strategy, and optional description. Each simple alias can point to only one fleet, but a fleet can have multiple aliases. If successful, a new alias record is returned, including an alias ID, which you can reference when creating a game session. You can reassign an alias to another fleet by calling <code>UpdateAlias</code>.</p> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateAlias">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createAliasRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateAlias (
        UObject *WorldContextObject,
        bool &success,
        FGameLiftCreateAliasRequest createAliasRequest,
        FGameLiftCreateAliasResult &createAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates a new Amazon GameLift build record for your game server binary files and points to the location of your game server build files in an Amazon Simple Storage Service (Amazon S3) location. </p> <p>Game server binaries must be combined into a <code>.zip</code> file for use with Amazon GameLift. </p> <important> <p>To create new builds quickly and easily, use the AWS CLI command <b> <a href="https://docs.aws.amazon.com/cli/latest/reference/gamelift/upload-build.html">upload-build</a> </b>. This helper command uploads your build and creates a new build record in one step, and automatically handles the necessary permissions. </p> </important> <p>The <code>CreateBuild</code> operation should be used only when you need to manually upload your build files, as in the following scenarios:</p> <ul> <li> <p>Store a build file in an Amazon S3 bucket under your own AWS account. To use this option, you must first give Amazon GameLift access to that Amazon S3 bucket. To create a new build record using files in your Amazon S3 bucket, call <code>CreateBuild</code> and specify a build name, operating system, and the storage location of your game build.</p> </li> <li> <p>Upload a build file directly to Amazon GameLift's Amazon S3 account. To use this option, you first call <code>CreateBuild</code> with a build name and operating system. This action creates a new build record and returns an Amazon S3 storage location (bucket and key only) and temporary access credentials. Use the credentials to manually upload your build file to the storage location (see the Amazon S3 topic <a href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UploadingObjects.html">Uploading Objects</a>). You can upload files to a location only once. </p> </li> </ul> <p>If successful, this operation creates a new build record with a unique build ID and places it in <code>INITIALIZED</code> status. You can use <a>DescribeBuild</a> to check the status of your build. A build must be in <code>READY</code> status before it can be used to create fleets.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-build-intro.html">Uploading Your Game</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-build-cli-uploading.html#gamelift-build-cli-uploading-create-build"> Create a Build with Files in Amazon S3</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateBuild">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createBuildRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateBuild (
        UObject *WorldContextObject,
        bool &success,
        FCreateBuildRequest createBuildRequest,
        FCreateBuildResult &createBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates a new fleet to run your game servers. whether they are custom game builds or Realtime Servers with game-specific script. A fleet is a set of Amazon Elastic Compute Cloud (Amazon EC2) instances, each of which can host multiple game sessions. When creating a fleet, you choose the hardware specifications, set some configuration options, and specify the game server to deploy on the new fleet. </p> <p>To create a new fleet, you must provide the following: (1) a fleet name, (2) an EC2 instance type and fleet type (spot or on-demand), (3) the build ID for your game build or script ID if using Realtime Servers, and (4) a run-time configuration, which determines how game servers will run on each instance in the fleet. </p> <note> <p>When creating a Realtime Servers fleet, we recommend using a minimal version of the Realtime script (see this <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-script.html#realtime-script-examples"> working code example </a>). This will make it much easier to troubleshoot any fleet creation issues. Once the fleet is active, you can update your Realtime script as needed.</p> </note> <p>If the <code>CreateFleet</code> call is successful, Amazon GameLift performs the following tasks. You can track the process of a fleet by checking the fleet status or by monitoring fleet creation events:</p> <ul> <li> <p>Creates a fleet record. Status: <code>NEW</code>.</p> </li> <li> <p>Begins writing events to the fleet event log, which can be accessed in the Amazon GameLift console.</p> <p>Sets the fleet's target capacity to 1 (desired instances), which triggers Amazon GameLift to start one new EC2 instance.</p> </li> <li> <p>Downloads the game build or Realtime script to the new instance and installs it. Statuses: <code>DOWNLOADING</code>, <code>VALIDATING</code>, <code>BUILDING</code>. </p> </li> <li> <p>Starts launching server processes on the instance. If the fleet is configured to run multiple server processes per instance, Amazon GameLift staggers each launch by a few seconds. Status: <code>ACTIVATING</code>.</p> </li> <li> <p>Sets the fleet's status to <code>ACTIVE</code> as soon as one server process is ready to host a game session.</p> </li> </ul> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-creating-debug.html"> Debug Fleet Creation Issues</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateFleet">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createFleetRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateFleet (
        UObject *WorldContextObject,
        bool &success,
        FCreateFleetRequest createFleetRequest,
        FCreateFleetResult &createFleetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates a multiplayer game session for players. This action creates a game session record and assigns an available server process in the specified fleet to host the game session. A fleet must have an <code>ACTIVE</code> status before a game session can be created in it.</p> <p>To create a game session, specify either fleet ID or alias ID and indicate a maximum number of players to allow in the game session. You can also provide a name and game-specific properties for this game session. If successful, a <a>GameSession</a> object is returned containing the game session properties and other settings you specified.</p> <p> <b>Idempotency tokens.</b> You can add a token that uniquely identifies game session requests. This is useful for ensuring that game session requests are idempotent. Multiple requests with the same idempotency token are processed only once; subsequent requests return the original result. All response values are the same with the exception of game session status, which may change.</p> <p> <b>Resource creation limits.</b> If you are creating a game session on a fleet with a resource creation limit policy in force, then you must specify a creator ID. Without this ID, Amazon GameLift has no way to evaluate the policy for this new game session request.</p> <p> <b>Player acceptance policy.</b> By default, newly created game sessions are open to new players. You can restrict new player access by using <a>UpdateGameSession</a> to change the game session's player session creation policy.</p> <p> <b>Game session logs.</b> Logs are retained for all active game sessions for 14 days. To access the logs, call <a>GetGameSessionLogUrl</a> to download the log files.</p> <p> <i>Available in Amazon GameLift Local.</i> </p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateGameSession">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createGameSessionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateGameSession (
        UObject *WorldContextObject,
        bool &success,
        FCreateGameSessionRequest createGameSessionRequest,
        FCreateGameSessionResult &createGameSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Establishes a new queue for processing requests to place new game sessions. A queue identifies where new game sessions can be hosted -- by specifying a list of destinations (fleets or aliases) -- and how long requests can wait in the queue before timing out. You can set up a queue to try to place game sessions on fleets in multiple regions. To add placement requests to a queue, call <a>StartGameSessionPlacement</a> and reference the queue name.</p> <p> <b>Destination order.</b> When processing a request for a game session, Amazon GameLift tries each destination in order until it finds one with available resources to host the new game session. A queue's default order is determined by how destinations are listed. The default order is overridden when a game session placement request provides player latency information. Player latency information enables Amazon GameLift to prioritize destinations where players report the lowest average latency, as a result placing the new game session where the majority of players will have the best possible gameplay experience.</p> <p> <b>Player latency policies.</b> For placement requests containing player latency information, use player latency policies to protect individual players from very high latencies. With a latency cap, even when a destination can deliver a low latency for most players, the game is not placed where any individual player is reporting latency higher than a policy's maximum. A queue can have multiple latency policies, which are enforced consecutively starting with the policy with the lowest latency cap. Use multiple policies to gradually relax latency controls; for example, you might set a policy with a low latency cap for the first 60 seconds, a second policy with a higher cap for the next 60 seconds, etc. </p> <p>To create a new queue, provide a name, timeout value, a list of destinations and, if desired, a set of latency policies. If successful, a new queue object is returned.</p> <ul> <li> <p> <a>CreateGameSessionQueue</a> </p> </li> <li> <p> <a>DescribeGameSessionQueues</a> </p> </li> <li> <p> <a>UpdateGameSessionQueue</a> </p> </li> <li> <p> <a>DeleteGameSessionQueue</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateGameSessionQueue">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createGameSessionQueueRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateGameSessionQueue (
        UObject *WorldContextObject,
        bool &success,
        FCreateGameSessionQueueRequest createGameSessionQueueRequest,
        FCreateGameSessionQueueResult &createGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Defines a new matchmaking configuration for use with FlexMatch. A matchmaking configuration sets out guidelines for matching players and getting the matches into games. You can set up multiple matchmaking configurations to handle the scenarios needed for your game. Each matchmaking ticket (<a>StartMatchmaking</a> or <a>StartMatchBackfill</a>) specifies a configuration for the match and provides player attributes to support the configuration being used. </p> <p>To create a matchmaking configuration, at a minimum you must specify the following: configuration name; a rule set that governs how to evaluate players and find acceptable matches; a game session queue to use when placing a new game session for the match; and the maximum time allowed for a matchmaking attempt.</p> <p>There are two ways to track the progress of matchmaking tickets: (1) polling ticket status with <a>DescribeMatchmaking</a>; or (2) receiving notifications with Amazon Simple Notification Service (SNS). To use notifications, you first need to set up an SNS topic to receive the notifications, and provide the topic ARN in the matchmaking configuration. Since notifications promise only "best effort" delivery, we recommend calling <code>DescribeMatchmaking</code> if no notifications are received within 30 seconds.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-configuration.html"> Design a FlexMatch Matchmaker</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-notification.html"> Setting up Notifications for Matchmaking</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateMatchmakingConfiguration">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createMatchmakingConfigurationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateMatchmakingConfiguration (
        UObject *WorldContextObject,
        bool &success,
        FCreateMatchmakingConfigurationRequest createMatchmakingConfigurationRequest,
        FCreateMatchmakingConfigurationResult &createMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates a new rule set for FlexMatch matchmaking. A rule set describes the type of match to create, such as the number and size of teams, and sets the parameters for acceptable player matches, such as minimum skill level or character type. A rule set is used by a <a>MatchmakingConfiguration</a>. </p> <p>To create a matchmaking rule set, provide unique rule set name and the rule set body in JSON format. Rule sets must be defined in the same region as the matchmaking configuration they are used with.</p> <p>Since matchmaking rule sets cannot be edited, it is a good idea to check the rule set syntax using <a>ValidateMatchmakingRuleSet</a> before creating a new rule set.</p> <p> <b>Learn more</b> </p> <ul> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-rulesets.html">Build a Rule Set</a> </p> </li> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-configuration.html">Design a Matchmaker</a> </p> </li> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-intro.html">Matchmaking with FlexMatch</a> </p> </li> </ul> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateMatchmakingRuleSet">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createMatchmakingRuleSetRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateMatchmakingRuleSet (
        UObject *WorldContextObject,
        bool &success,
        FCreateMatchmakingRuleSetRequest createMatchmakingRuleSetRequest,
        FCreateMatchmakingRuleSetResult &createMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Reserves an open player slot in an active game session. Before a player can be added, a game session must have an <code>ACTIVE</code> status, have a creation policy of <code>ALLOW_ALL</code>, and have an open player slot. To add a group of players to a game session, use <a>CreatePlayerSessions</a>. When the player connects to the game server and references a player session ID, the game server contacts the Amazon GameLift service to validate the player reservation and accept the player.</p> <p>To create a player session, specify a game session ID, player ID, and optionally a string of player data. If successful, a slot is reserved in the game session for the player and a new <a>PlayerSession</a> object is returned. Player sessions cannot be updated. </p> <p> <i>Available in Amazon GameLift Local.</i> </p> <ul> <li> <p> <a>CreatePlayerSession</a> </p> </li> <li> <p> <a>CreatePlayerSessions</a> </p> </li> <li> <p> <a>DescribePlayerSessions</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreatePlayerSession">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createPlayerSessionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreatePlayerSession (
        UObject *WorldContextObject,
        bool &success,
        FCreatePlayerSessionRequest createPlayerSessionRequest,
        FCreatePlayerSessionResult &createPlayerSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Reserves open slots in a game session for a group of players. Before players can be added, a game session must have an <code>ACTIVE</code> status, have a creation policy of <code>ALLOW_ALL</code>, and have an open player slot. To add a single player to a game session, use <a>CreatePlayerSession</a>. When a player connects to the game server and references a player session ID, the game server contacts the Amazon GameLift service to validate the player reservation and accept the player.</p> <p>To create player sessions, specify a game session ID, a list of player IDs, and optionally a set of player data strings. If successful, a slot is reserved in the game session for each player and a set of new <a>PlayerSession</a> objects is returned. Player sessions cannot be updated.</p> <p> <i>Available in Amazon GameLift Local.</i> </p> <ul> <li> <p> <a>CreatePlayerSession</a> </p> </li> <li> <p> <a>CreatePlayerSessions</a> </p> </li> <li> <p> <a>DescribePlayerSessions</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreatePlayerSessions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createPlayerSessionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreatePlayerSessions (
        UObject *WorldContextObject,
        bool &success,
        FCreatePlayerSessionsRequest createPlayerSessionsRequest,
        FCreatePlayerSessionsResult &createPlayerSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates a new script record for your Realtime Servers script. Realtime scripts are JavaScript that provide configuration settings and optional custom game logic for your game. The script is deployed when you create a Realtime Servers fleet to host your game sessions. Script logic is executed during an active game session. </p> <p>To create a new script record, specify a script name and provide the script file(s). The script files and all dependencies must be zipped into a single file. You can pull the zip file from either of these locations: </p> <ul> <li> <p>A locally available directory. Use the <i>ZipFile</i> parameter for this option.</p> </li> <li> <p>An Amazon Simple Storage Service (Amazon S3) bucket under your AWS account. Use the <i>StorageLocation</i> parameter for this option. You'll need to have an Identity Access Management (IAM) role that allows the Amazon GameLift service to access your S3 bucket. </p> </li> </ul> <p>If the call is successful, a new script record is created with a unique script ID. If the script file is provided as a local file, the file is uploaded to an Amazon GameLift-owned S3 bucket and the script record's storage location reflects this location. If the script file is provided as an S3 bucket, Amazon GameLift accesses the file at this storage location as needed for deployment.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-intro.html">Amazon GameLift Realtime Servers</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/setting-up-role.html">Set Up a Role for Amazon GameLift Access</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateScript</a> </p> </li> <li> <p> <a>ListScripts</a> </p> </li> <li> <p> <a>DescribeScript</a> </p> </li> <li> <p> <a>UpdateScript</a> </p> </li> <li> <p> <a>DeleteScript</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateScript">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createScriptRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateScript (
        UObject *WorldContextObject,
        bool &success,
        FCreateScriptRequest createScriptRequest,
        FCreateScriptResult &createScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Requests authorization to create or delete a peer connection between the VPC for your Amazon GameLift fleet and a virtual private cloud (VPC) in your AWS account. VPC peering enables the game servers on your fleet to communicate directly with other AWS resources. Once you've received authorization, call <a>CreateVpcPeeringConnection</a> to establish the peering connection. For more information, see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/vpc-peering.html">VPC Peering with Amazon GameLift Fleets</a>.</p> <p>You can peer with VPCs that are owned by any AWS account you have access to, including the account that you use to manage your Amazon GameLift fleets. You cannot peer with VPCs that are in different regions.</p> <p>To request authorization to create a connection, call this operation from the AWS account with the VPC that you want to peer to your Amazon GameLift fleet. For example, to enable your game servers to retrieve data from a DynamoDB table, use the account that manages that DynamoDB resource. Identify the following values: (1) The ID of the VPC that you want to peer with, and (2) the ID of the AWS account that you use to manage Amazon GameLift. If successful, VPC peering is authorized for the specified VPC. </p> <p>To request authorization to delete a connection, call this operation from the AWS account with the VPC that is peered with your Amazon GameLift fleet. Identify the following values: (1) VPC ID that you want to delete the peering connection for, and (2) ID of the AWS account that you use to manage Amazon GameLift. </p> <p>The authorization remains valid for 24 hours unless it is canceled by a call to <a>DeleteVpcPeeringAuthorization</a>. You must create or delete the peering connection while the authorization is valid. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateVpcPeeringAuthorization">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createVpcPeeringAuthorizationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateVpcPeeringAuthorization (
        UObject *WorldContextObject,
        bool &success,
        FCreateVpcPeeringAuthorizationRequest createVpcPeeringAuthorizationRequest,
        FCreateVpcPeeringAuthorizationResult &createVpcPeeringAuthorizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Establishes a VPC peering connection between a virtual private cloud (VPC) in an AWS account with the VPC for your Amazon GameLift fleet. VPC peering enables the game servers on your fleet to communicate directly with other AWS resources. You can peer with VPCs in any AWS account that you have access to, including the account that you use to manage your Amazon GameLift fleets. You cannot peer with VPCs that are in different regions. For more information, see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/vpc-peering.html">VPC Peering with Amazon GameLift Fleets</a>.</p> <p>Before calling this operation to establish the peering connection, you first need to call <a>CreateVpcPeeringAuthorization</a> and identify the VPC you want to peer with. Once the authorization for the specified VPC is issued, you have 24 hours to establish the connection. These two operations handle all tasks necessary to peer the two VPCs, including acceptance, updating routing tables, etc. </p> <p>To establish the connection, call this operation from the AWS account that is used to manage the Amazon GameLift fleets. Identify the following values: (1) The ID of the fleet you want to be enable a VPC peering connection for; (2) The AWS account with the VPC that you want to peer with; and (3) The ID of the VPC you want to peer with. This operation is asynchronous. If successful, a <a>VpcPeeringConnection</a> request is created. You can use continuous polling to track the request's status using <a>DescribeVpcPeeringConnections</a>, or by monitoring fleet events for success or failure using <a>DescribeFleetEvents</a>. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/CreateVpcPeeringConnection">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param createVpcPeeringConnectionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void CreateVpcPeeringConnection (
        UObject *WorldContextObject,
        bool &success,
        FCreateVpcPeeringConnectionRequest createVpcPeeringConnectionRequest,
        FCreateVpcPeeringConnectionResult &createVpcPeeringConnectionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes an alias. This action removes all record of the alias. Game clients attempting to access a server process using the deleted alias receive an error. To delete an alias, specify the alias ID to be deleted.</p> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteAlias">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteAliasRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteAlias (
        UObject *WorldContextObject,
        bool &success,
        FGameLiftDeleteAliasRequest deleteAliasRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes a build. This action permanently deletes the build record and any uploaded build files.</p> <p>To delete a build, specify its ID. Deleting a build does not affect the status of any active fleets using the build, but you can no longer create new fleets with the deleted build.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/build-intro.html"> Working with Builds</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteBuild">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteBuildRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteBuild (
        UObject *WorldContextObject,
        bool &success,
        FDeleteBuildRequest deleteBuildRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes everything related to a fleet. Before deleting a fleet, you must set the fleet's desired capacity to zero. See <a>UpdateFleetCapacity</a>.</p> <p>If the fleet being deleted has a VPC peering connection, you first need to get a valid authorization (good for 24 hours) by calling <a>CreateVpcPeeringAuthorization</a>. You do not need to explicitly delete the VPC peering connection--this is done as part of the delete fleet process.</p> <p>This action removes the fleet's resources and the fleet record. Once a fleet is deleted, you can no longer use that fleet.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteFleet">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteFleetRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteFleet (
        UObject *WorldContextObject,
        bool &success,
        FDeleteFleetRequest deleteFleetRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes a game session queue. This action means that any <a>StartGameSessionPlacement</a> requests that reference this queue will fail. To delete a queue, specify the queue name.</p> <ul> <li> <p> <a>CreateGameSessionQueue</a> </p> </li> <li> <p> <a>DescribeGameSessionQueues</a> </p> </li> <li> <p> <a>UpdateGameSessionQueue</a> </p> </li> <li> <p> <a>DeleteGameSessionQueue</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteGameSessionQueue">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteGameSessionQueueRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteGameSessionQueue (
        UObject *WorldContextObject,
        bool &success,
        FDeleteGameSessionQueueRequest deleteGameSessionQueueRequest,
        FDeleteGameSessionQueueResult &deleteGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Permanently removes a FlexMatch matchmaking configuration. To delete, specify the configuration name. A matchmaking configuration cannot be deleted if it is being used in any active matchmaking tickets.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteMatchmakingConfiguration">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteMatchmakingConfigurationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteMatchmakingConfiguration (
        UObject *WorldContextObject,
        bool &success,
        FDeleteMatchmakingConfigurationRequest deleteMatchmakingConfigurationRequest,
        FDeleteMatchmakingConfigurationResult &deleteMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes an existing matchmaking rule set. To delete the rule set, provide the rule set name. Rule sets cannot be deleted if they are currently being used by a matchmaking configuration. </p> <p> <b>Learn more</b> </p> <ul> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-rulesets.html">Build a Rule Set</a> </p> </li> </ul> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteMatchmakingRuleSet">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteMatchmakingRuleSetRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteMatchmakingRuleSet (
        UObject *WorldContextObject,
        bool &success,
        FDeleteMatchmakingRuleSetRequest deleteMatchmakingRuleSetRequest,
        FDeleteMatchmakingRuleSetResult &deleteMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes a fleet scaling policy. This action means that the policy is no longer in force and removes all record of it. To delete a scaling policy, specify both the scaling policy name and the fleet ID it is associated with.</p> <p>To temporarily suspend scaling policies, call <a>StopFleetActions</a>. This operation suspends all policies for the fleet.</p> <ul> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p>Manage scaling policies:</p> <ul> <li> <p> <a>PutScalingPolicy</a> (auto-scaling)</p> </li> <li> <p> <a>DescribeScalingPolicies</a> (auto-scaling)</p> </li> <li> <p> <a>DeleteScalingPolicy</a> (auto-scaling)</p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteScalingPolicy">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteScalingPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteScalingPolicy (
        UObject *WorldContextObject,
        bool &success,
        FDeleteScalingPolicyRequest deleteScalingPolicyRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Deletes a Realtime script. This action permanently deletes the script record. If script files were uploaded, they are also deleted (files stored in an S3 bucket are not deleted). </p> <p>To delete a script, specify the script ID. Before deleting a script, be sure to terminate all fleets that are deployed with the script being deleted. Fleet instances periodically check for script updates, and if the script record no longer exists, the instance will go into an error state and be unable to host game sessions.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-intro.html">Amazon GameLift Realtime Servers</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateScript</a> </p> </li> <li> <p> <a>ListScripts</a> </p> </li> <li> <p> <a>DescribeScript</a> </p> </li> <li> <p> <a>UpdateScript</a> </p> </li> <li> <p> <a>DeleteScript</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteScript">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteScriptRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteScript (
        UObject *WorldContextObject,
        bool &success,
        FDeleteScriptRequest deleteScriptRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Cancels a pending VPC peering authorization for the specified VPC. If you need to delete an existing VPC peering connection, call <a>DeleteVpcPeeringConnection</a>. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteVpcPeeringAuthorization">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteVpcPeeringAuthorizationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteVpcPeeringAuthorization (
        UObject *WorldContextObject,
        bool &success,
        FDeleteVpcPeeringAuthorizationRequest deleteVpcPeeringAuthorizationRequest,
        FDeleteVpcPeeringAuthorizationResult &deleteVpcPeeringAuthorizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Removes a VPC peering connection. To delete the connection, you must have a valid authorization for the VPC peering connection that you want to delete. You can check for an authorization by calling <a>DescribeVpcPeeringAuthorizations</a> or request a new one using <a>CreateVpcPeeringAuthorization</a>. </p> <p>Once a valid authorization exists, call this operation from the AWS account that is used to manage the Amazon GameLift fleets. Identify the connection to delete by the connection ID and fleet ID. If successful, the connection is removed. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DeleteVpcPeeringConnection">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param deleteVpcPeeringConnectionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DeleteVpcPeeringConnection (
        UObject *WorldContextObject,
        bool &success,
        FDeleteVpcPeeringConnectionRequest deleteVpcPeeringConnectionRequest,
        FDeleteVpcPeeringConnectionResult &deleteVpcPeeringConnectionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties for an alias. This operation returns all alias metadata and settings. To get an alias's target fleet ID only, use <code>ResolveAlias</code>. </p> <p>To get alias properties, specify the alias ID. If successful, the requested alias record is returned.</p> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeAlias">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeAliasRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeAlias (
        UObject *WorldContextObject,
        bool &success,
        FDescribeAliasRequest describeAliasRequest,
        FDescribeAliasResult &describeAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties for a build. To request a build record, specify a build ID. If successful, an object containing the build properties is returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/build-intro.html"> Working with Builds</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeBuild">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeBuildRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeBuild (
        UObject *WorldContextObject,
        bool &success,
        FDescribeBuildRequest describeBuildRequest,
        FDescribeBuildResult &describeBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the following information for the specified EC2 instance type:</p> <ul> <li> <p>maximum number of instances allowed per AWS account (service limit)</p> </li> <li> <p>current usage level for the AWS account</p> </li> </ul> <p>Service limits vary depending on region. Available regions for Amazon GameLift can be found in the AWS Management Console for Amazon GameLift (see the drop-down list in the upper right corner).</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeEC2InstanceLimits">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeEC2InstanceLimitsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeEC2InstanceLimits (
        UObject *WorldContextObject,
        bool &success,
        FDescribeEC2InstanceLimitsRequest describeEC2InstanceLimitsRequest,
        FDescribeEC2InstanceLimitsResult &describeEC2InstanceLimitsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves fleet properties, including metadata, status, and configuration, for one or more fleets. You can request attributes for all fleets, or specify a list of one or more fleet IDs. When requesting multiple fleets, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>FleetAttributes</a> object is returned for each requested fleet ID. When specifying a list of fleet IDs, attribute objects are returned only for fleets that currently exist. </p> <note> <p>Some API actions may limit the number of fleet IDs allowed in one request. If a request exceeds this limit, the request fails and the error message includes the maximum allowed.</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeFleetAttributes">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeFleetAttributesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeFleetAttributes (
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetAttributesRequest describeFleetAttributesRequest,
        FDescribeFleetAttributesResult &describeFleetAttributesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the current status of fleet capacity for one or more fleets. This information includes the number of instances that have been requested for the fleet and the number currently active. You can request capacity for all fleets, or specify a list of one or more fleet IDs. When requesting multiple fleets, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>FleetCapacity</a> object is returned for each requested fleet ID. When specifying a list of fleet IDs, attribute objects are returned only for fleets that currently exist. </p> <note> <p>Some API actions may limit the number of fleet IDs allowed in one request. If a request exceeds this limit, the request fails and the error message includes the maximum allowed.</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeFleetCapacity">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeFleetCapacityRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeFleetCapacity (
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetCapacityRequest describeFleetCapacityRequest,
        FDescribeFleetCapacityResult &describeFleetCapacityResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves entries from the specified fleet's event log. You can specify a time range to limit the result set. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, a collection of event log entries matching the request are returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeFleetEvents">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeFleetEventsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeFleetEvents (
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetEventsRequest describeFleetEventsRequest,
        FDescribeFleetEventsResult &describeFleetEventsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the inbound connection permissions for a fleet. Connection permissions include a range of IP addresses and port settings that incoming traffic can use to access server processes in the fleet. To get a fleet's inbound connection permissions, specify a fleet ID. If successful, a collection of <a>IpPermission</a> objects is returned for the requested fleet ID. If the requested fleet has been deleted, the result set is empty.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeFleetPortSettings">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeFleetPortSettingsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeFleetPortSettings (
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetPortSettingsRequest describeFleetPortSettingsRequest,
        FDescribeFleetPortSettingsResult &describeFleetPortSettingsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves utilization statistics for one or more fleets. You can request utilization data for all fleets, or specify a list of one or more fleet IDs. When requesting multiple fleets, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>FleetUtilization</a> object is returned for each requested fleet ID. When specifying a list of fleet IDs, utilization objects are returned only for fleets that currently exist. </p> <note> <p>Some API actions may limit the number of fleet IDs allowed in one request. If a request exceeds this limit, the request fails and the error message includes the maximum allowed.</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeFleetUtilization">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeFleetUtilizationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeFleetUtilization (
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetUtilizationRequest describeFleetUtilizationRequest,
        FDescribeFleetUtilizationResult &describeFleetUtilizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties, including the protection policy in force, for one or more game sessions. This action can be used in several ways: (1) provide a <code>GameSessionId</code> or <code>GameSessionArn</code> to request details for a specific game session; (2) provide either a <code>FleetId</code> or an <code>AliasId</code> to request properties for all game sessions running on a fleet. </p> <p>To get game session record(s), specify just one of the following: game session ID, fleet ID, or alias ID. You can filter this request by game session status. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>GameSessionDetail</a> object is returned for each session matching the request.</p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeGameSessionDetails">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeGameSessionDetailsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeGameSessionDetails (
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionDetailsRequest describeGameSessionDetailsRequest,
        FDescribeGameSessionDetailsResult &describeGameSessionDetailsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties and current status of a game session placement request. To get game session placement details, specify the placement ID. If successful, a <a>GameSessionPlacement</a> object is returned.</p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeGameSessionPlacement">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeGameSessionPlacementRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeGameSessionPlacement (
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionPlacementRequest describeGameSessionPlacementRequest,
        FDescribeGameSessionPlacementResult &describeGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the properties for one or more game session queues. When requesting multiple queues, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>GameSessionQueue</a> object is returned for each requested queue. When specifying a list of queues, objects are returned only for queues that currently exist in the region.</p> <ul> <li> <p> <a>CreateGameSessionQueue</a> </p> </li> <li> <p> <a>DescribeGameSessionQueues</a> </p> </li> <li> <p> <a>UpdateGameSessionQueue</a> </p> </li> <li> <p> <a>DeleteGameSessionQueue</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeGameSessionQueues">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeGameSessionQueuesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeGameSessionQueues (
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionQueuesRequest describeGameSessionQueuesRequest,
        FDescribeGameSessionQueuesResult &describeGameSessionQueuesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves a set of one or more game sessions. Request a specific game session or request all game sessions on a fleet. Alternatively, use <a>SearchGameSessions</a> to request a set of active game sessions that are filtered by certain criteria. To retrieve protection policy settings for game sessions, use <a>DescribeGameSessionDetails</a>.</p> <p>To get game sessions, specify one of the following: game session ID, fleet ID, or alias ID. You can filter this request by game session status. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>GameSession</a> object is returned for each game session matching the request.</p> <p> <i>Available in Amazon GameLift Local.</i> </p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeGameSessions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeGameSessionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeGameSessions (
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionsRequest describeGameSessionsRequest,
        FDescribeGameSessionsResult &describeGameSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves information about a fleet's instances, including instance IDs. Use this action to get details on all instances in the fleet or get details on one specific instance.</p> <p>To get a specific instance, specify fleet ID and instance ID. To get all instances in a fleet, specify a fleet ID only. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, an <a>Instance</a> object is returned for each result.</p><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeInstances">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeInstancesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeInstances (
        UObject *WorldContextObject,
        bool &success,
        FDescribeInstancesRequest describeInstancesRequest,
        FDescribeInstancesResult &describeInstancesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves one or more matchmaking tickets. Use this operation to retrieve ticket information, including status and--once a successful match is made--acquire connection information for the resulting new game session. </p> <p>You can use this operation to track the progress of matchmaking requests (through polling) as an alternative to using event notifications. See more details on tracking matchmaking requests through polling or notifications in <a>StartMatchmaking</a>. </p> <p>To request matchmaking tickets, provide a list of up to 10 ticket IDs. If the request is successful, a ticket object is returned for each requested ID that currently exists.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-client.html"> Add FlexMatch to a Game Client</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguidematch-notification.html"> Set Up FlexMatch Event Notification</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>StartMatchmaking</a> </p> </li> <li> <p> <a>DescribeMatchmaking</a> </p> </li> <li> <p> <a>StopMatchmaking</a> </p> </li> <li> <p> <a>AcceptMatch</a> </p> </li> <li> <p> <a>StartMatchBackfill</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeMatchmaking">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeMatchmakingRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeMatchmaking (
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingRequest describeMatchmakingRequest,
        FDescribeMatchmakingResult &describeMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the details of FlexMatch matchmaking configurations. With this operation, you have the following options: (1) retrieve all existing configurations, (2) provide the names of one or more configurations to retrieve, or (3) retrieve all configurations that use a specified rule set name. When requesting multiple items, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a configuration is returned for each requested name. When specifying a list of names, only configurations that currently exist are returned. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/matchmaker-build.html"> Setting Up FlexMatch Matchmakers</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeMatchmakingConfigurations">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeMatchmakingConfigurationsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeMatchmakingConfigurations (
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingConfigurationsRequest describeMatchmakingConfigurationsRequest,
        FDescribeMatchmakingConfigurationsResult &describeMatchmakingConfigurationsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the details for FlexMatch matchmaking rule sets. You can request all existing rule sets for the region, or provide a list of one or more rule set names. When requesting multiple items, use the pagination parameters to retrieve results as a set of sequential pages. If successful, a rule set is returned for each requested name. </p> <p> <b>Learn more</b> </p> <ul> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-rulesets.html">Build a Rule Set</a> </p> </li> </ul> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeMatchmakingRuleSets">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeMatchmakingRuleSetsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeMatchmakingRuleSets (
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingRuleSetsRequest describeMatchmakingRuleSetsRequest,
        FDescribeMatchmakingRuleSetsResult &describeMatchmakingRuleSetsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties for one or more player sessions. This action can be used in several ways: (1) provide a <code>PlayerSessionId</code> to request properties for a specific player session; (2) provide a <code>GameSessionId</code> to request properties for all player sessions in the specified game session; (3) provide a <code>PlayerId</code> to request properties for all player sessions of a specified player. </p> <p>To get game session record(s), specify only one of the following: a player session ID, a game session ID, or a player ID. You can filter this request by player session status. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, a <a>PlayerSession</a> object is returned for each session matching the request.</p> <p> <i>Available in Amazon GameLift Local.</i> </p> <ul> <li> <p> <a>CreatePlayerSession</a> </p> </li> <li> <p> <a>CreatePlayerSessions</a> </p> </li> <li> <p> <a>DescribePlayerSessions</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribePlayerSessions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describePlayerSessionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribePlayerSessions (
        UObject *WorldContextObject,
        bool &success,
        FDescribePlayerSessionsRequest describePlayerSessionsRequest,
        FDescribePlayerSessionsResult &describePlayerSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the current run-time configuration for the specified fleet. The run-time configuration tells Amazon GameLift how to launch server processes on instances in the fleet.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeRuntimeConfiguration">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeRuntimeConfigurationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeRuntimeConfiguration (
        UObject *WorldContextObject,
        bool &success,
        FDescribeRuntimeConfigurationRequest describeRuntimeConfigurationRequest,
        FDescribeRuntimeConfigurationResult &describeRuntimeConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves all scaling policies applied to a fleet.</p> <p>To get a fleet's scaling policies, specify the fleet ID. You can filter this request by policy status, such as to retrieve only active scaling policies. Use the pagination parameters to retrieve results as a set of sequential pages. If successful, set of <a>ScalingPolicy</a> objects is returned for the fleet.</p> <p>A fleet may have all of its scaling policies suspended (<a>StopFleetActions</a>). This action does not affect the status of the scaling policies, which remains ACTIVE. To see whether a fleet's scaling policies are in force or suspended, call <a>DescribeFleetAttributes</a> and check the stopped actions.</p> <ul> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p>Manage scaling policies:</p> <ul> <li> <p> <a>PutScalingPolicy</a> (auto-scaling)</p> </li> <li> <p> <a>DescribeScalingPolicies</a> (auto-scaling)</p> </li> <li> <p> <a>DeleteScalingPolicy</a> (auto-scaling)</p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeScalingPolicies">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeScalingPoliciesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeScalingPolicies (
        UObject *WorldContextObject,
        bool &success,
        FDescribeScalingPoliciesRequest describeScalingPoliciesRequest,
        FDescribeScalingPoliciesResult &describeScalingPoliciesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves properties for a Realtime script. </p> <p>To request a script record, specify the script ID. If successful, an object containing the script properties is returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-intro.html">Amazon GameLift Realtime Servers</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateScript</a> </p> </li> <li> <p> <a>ListScripts</a> </p> </li> <li> <p> <a>DescribeScript</a> </p> </li> <li> <p> <a>UpdateScript</a> </p> </li> <li> <p> <a>DeleteScript</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeScript">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeScriptRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeScript (
        UObject *WorldContextObject,
        bool &success,
        FDescribeScriptRequest describeScriptRequest,
        FDescribeScriptResult &describeScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves valid VPC peering authorizations that are pending for the AWS account. This operation returns all VPC peering authorizations and requests for peering. This includes those initiated and received by this account. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeVpcPeeringAuthorizations">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeVpcPeeringAuthorizationsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeVpcPeeringAuthorizations (
        UObject *WorldContextObject,
        bool &success,
        FDescribeVpcPeeringAuthorizationsRequest describeVpcPeeringAuthorizationsRequest,
        FDescribeVpcPeeringAuthorizationsResult &describeVpcPeeringAuthorizationsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves information on VPC peering connections. Use this operation to get peering information for all fleets or for one specific fleet ID. </p> <p>To retrieve connection information, call this operation from the AWS account that is used to manage the Amazon GameLift fleets. Specify a fleet ID or leave the parameter empty to retrieve all connection records. If successful, the retrieved information includes both active and pending connections. Active connections identify the IpV4 CIDR block that the VPC uses to connect. </p> <ul> <li> <p> <a>CreateVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>DescribeVpcPeeringAuthorizations</a> </p> </li> <li> <p> <a>DeleteVpcPeeringAuthorization</a> </p> </li> <li> <p> <a>CreateVpcPeeringConnection</a> </p> </li> <li> <p> <a>DescribeVpcPeeringConnections</a> </p> </li> <li> <p> <a>DeleteVpcPeeringConnection</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/DescribeVpcPeeringConnections">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param describeVpcPeeringConnectionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void DescribeVpcPeeringConnections (
        UObject *WorldContextObject,
        bool &success,
        FDescribeVpcPeeringConnectionsRequest describeVpcPeeringConnectionsRequest,
        FDescribeVpcPeeringConnectionsResult &describeVpcPeeringConnectionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the location of stored game session logs for a specified game session. When a game session is terminated, Amazon GameLift automatically stores the logs in Amazon S3 and retains them for 14 days. Use this URL to download the logs.</p> <note> <p>See the <a href="https://docs.aws.amazon.com/general/latest/gr/aws_service_limits.html#limits_gamelift">AWS Service Limits</a> page for maximum log file sizes. Log files that exceed this limit are not saved.</p> </note> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/GetGameSessionLogUrl">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param getGameSessionLogUrlRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void GetGameSessionLogUrl (
        UObject *WorldContextObject,
        bool &success,
        FGetGameSessionLogUrlRequest getGameSessionLogUrlRequest,
        FGetGameSessionLogUrlResult &getGameSessionLogUrlResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Requests remote access to a fleet instance. Remote access is useful for debugging, gathering benchmarking data, or watching activity in real time. </p> <p>Access requires credentials that match the operating system of the instance. For a Windows instance, Amazon GameLift returns a user name and password as strings for use with a Windows Remote Desktop client. For a Linux instance, Amazon GameLift returns a user name and RSA private key, also as strings, for use with an SSH client. The private key must be saved in the proper format to a <code>.pem</code> file before using. If you're making this request using the AWS CLI, saving the secret can be handled as part of the GetInstanceAccess request. (See the example later in this topic). For more information on remote access, see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-remote-access.html">Remotely Accessing an Instance</a>.</p> <p>To request access to a specific instance, specify the IDs of both the instance and the fleet it belongs to. You can retrieve a fleet's instance IDs by calling <a>DescribeInstances</a>. If successful, an <a>InstanceAccess</a> object is returned containing the instance's IP address and a set of credentials.</p><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/GetInstanceAccess">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param getInstanceAccessRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void GetInstanceAccess (
        UObject *WorldContextObject,
        bool &success,
        FGetInstanceAccessRequest getInstanceAccessRequest,
        FGetInstanceAccessResult &getInstanceAccessResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves all aliases for this AWS account. You can filter the result set by alias name and/or routing strategy type. Use the pagination parameters to retrieve results in sequential pages.</p> <note> <p>Returned aliases are not listed in any particular order.</p> </note> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ListAliases">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param listAliasesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ListAliases (
        UObject *WorldContextObject,
        bool &success,
        FGameLiftListAliasesRequest listAliasesRequest,
        FGameLiftListAliasesResult &listAliasesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves build records for all builds associated with the AWS account in use. You can limit results to builds that are in a specific status by using the <code>Status</code> parameter. Use the pagination parameters to retrieve results in a set of sequential pages. </p> <note> <p>Build records are not listed in any particular order.</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/build-intro.html"> Working with Builds</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ListBuilds">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param listBuildsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ListBuilds (
        UObject *WorldContextObject,
        bool &success,
        FListBuildsRequest listBuildsRequest,
        FListBuildsResult &listBuildsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves a collection of fleet records for this AWS account. You can filter the result set to find only those fleets that are deployed with a specific build or script. Use the pagination parameters to retrieve results in sequential pages.</p> <note> <p>Fleet records are not listed in a particular order.</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Set Up Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ListFleets">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param listFleetsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ListFleets (
        UObject *WorldContextObject,
        bool &success,
        FListFleetsRequest listFleetsRequest,
        FListFleetsResult &listFleetsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves script records for all Realtime scripts that are associated with the AWS account in use. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-intro.html">Amazon GameLift Realtime Servers</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateScript</a> </p> </li> <li> <p> <a>ListScripts</a> </p> </li> <li> <p> <a>DescribeScript</a> </p> </li> <li> <p> <a>UpdateScript</a> </p> </li> <li> <p> <a>DeleteScript</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ListScripts">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param listScriptsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ListScripts (
        UObject *WorldContextObject,
        bool &success,
        FListScriptsRequest listScriptsRequest,
        FListScriptsResult &listScriptsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Creates or updates a scaling policy for a fleet. Scaling policies are used to automatically scale a fleet's hosting capacity to meet player demand. An active scaling policy instructs Amazon GameLift to track a fleet metric and automatically change the fleet's capacity when a certain threshold is reached. There are two types of scaling policies: target-based and rule-based. Use a target-based policy to quickly and efficiently manage fleet scaling; this option is the most commonly used. Use rule-based policies when you need to exert fine-grained control over auto-scaling. </p> <p>Fleets can have multiple scaling policies of each type in force at the same time; you can have one target-based policy, one or multiple rule-based scaling policies, or both. We recommend caution, however, because multiple auto-scaling policies can have unintended consequences.</p> <p>You can temporarily suspend all scaling policies for a fleet by calling <a>StopFleetActions</a> with the fleet action AUTO_SCALING. To resume scaling policies, call <a>StartFleetActions</a> with the same fleet action. To stop just one scaling policy--or to permanently remove it, you must delete the policy with <a>DeleteScalingPolicy</a>.</p> <p>Learn more about how to work with auto-scaling in <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-autoscaling.html">Set Up Fleet Automatic Scaling</a>.</p> <p> <b>Target-based policy</b> </p> <p>A target-based policy tracks a single metric: PercentAvailableGameSessions. This metric tells us how much of a fleet's hosting capacity is ready to host game sessions but is not currently in use. This is the fleet's buffer; it measures the additional player demand that the fleet could handle at current capacity. With a target-based policy, you set your ideal buffer size and leave it to Amazon GameLift to take whatever action is needed to maintain that target. </p> <p>For example, you might choose to maintain a 10% buffer for a fleet that has the capacity to host 100 simultaneous game sessions. This policy tells Amazon GameLift to take action whenever the fleet's available capacity falls below or rises above 10 game sessions. Amazon GameLift will start new instances or stop unused instances in order to return to the 10% buffer. </p> <p>To create or update a target-based policy, specify a fleet ID and name, and set the policy type to "TargetBased". Specify the metric to track (PercentAvailableGameSessions) and reference a <a>TargetConfiguration</a> object with your desired buffer value. Exclude all other parameters. On a successful request, the policy name is returned. The scaling policy is automatically in force as soon as it's successfully created. If the fleet's auto-scaling actions are temporarily suspended, the new policy will be in force once the fleet actions are restarted.</p> <p> <b>Rule-based policy</b> </p> <p>A rule-based policy tracks specified fleet metric, sets a threshold value, and specifies the type of action to initiate when triggered. With a rule-based policy, you can select from several available fleet metrics. Each policy specifies whether to scale up or scale down (and by how much), so you need one policy for each type of action. </p> <p>For example, a policy may make the following statement: "If the percentage of idle instances is greater than 20% for more than 15 minutes, then reduce the fleet capacity by 10%."</p> <p>A policy's rule statement has the following structure:</p> <p>If <code>[MetricName]</code> is <code>[ComparisonOperator]</code> <code>[Threshold]</code> for <code>[EvaluationPeriods]</code> minutes, then <code>[ScalingAdjustmentType]</code> to/by <code>[ScalingAdjustment]</code>.</p> <p>To implement the example, the rule statement would look like this:</p> <p>If <code>[PercentIdleInstances]</code> is <code>[GreaterThanThreshold]</code> <code>[20]</code> for <code>[15]</code> minutes, then <code>[PercentChangeInCapacity]</code> to/by <code>[10]</code>.</p> <p>To create or update a scaling policy, specify a unique combination of name and fleet ID, and set the policy type to "RuleBased". Specify the parameter values for a policy rule statement. On a successful request, the policy name is returned. Scaling policies are automatically in force as soon as they're successfully created. If the fleet's auto-scaling actions are temporarily suspended, the new policy will be in force once the fleet actions are restarted.</p> <ul> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p>Manage scaling policies:</p> <ul> <li> <p> <a>PutScalingPolicy</a> (auto-scaling)</p> </li> <li> <p> <a>DescribeScalingPolicies</a> (auto-scaling)</p> </li> <li> <p> <a>DeleteScalingPolicy</a> (auto-scaling)</p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/PutScalingPolicy">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param putScalingPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void PutScalingPolicy (
        UObject *WorldContextObject,
        bool &success,
        FPutScalingPolicyRequest putScalingPolicyRequest,
        FPutScalingPolicyResult &putScalingPolicyResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves a fresh set of credentials for use when uploading a new set of game build files to Amazon GameLift's Amazon S3. This is done as part of the build creation process; see <a>CreateBuild</a>.</p> <p>To request new credentials, specify the build ID as returned with an initial <code>CreateBuild</code> request. If successful, a new set of credentials are returned, along with the S3 storage location associated with the build ID.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-build-intro.html">Uploading Your Game</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/RequestUploadCredentials">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param requestUploadCredentialsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void RequestUploadCredentials (
        UObject *WorldContextObject,
        bool &success,
        FRequestUploadCredentialsRequest requestUploadCredentialsRequest,
        FRequestUploadCredentialsResult &requestUploadCredentialsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves the fleet ID that a specified alias is currently pointing to.</p> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ResolveAlias">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param resolveAliasRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ResolveAlias (
        UObject *WorldContextObject,
        bool &success,
        FResolveAliasRequest resolveAliasRequest,
        FResolveAliasResult &resolveAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Retrieves all active game sessions that match a set of search criteria and sorts them in a specified order. You can search or sort by the following game session attributes:</p> <ul> <li> <p> <b>gameSessionId</b> -- Unique identifier for the game session. You can use either a <code>GameSessionId</code> or <code>GameSessionArn</code> value. </p> </li> <li> <p> <b>gameSessionName</b> -- Name assigned to a game session. This value is set when requesting a new game session with <a>CreateGameSession</a> or updating with <a>UpdateGameSession</a>. Game session names do not need to be unique to a game session.</p> </li> <li> <p> <b>gameSessionProperties</b> -- Custom data defined in a game session's <code>GameProperty</code> parameter. <code>GameProperty</code> values are stored as key:value pairs; the filter expression must indicate the key and a string to search the data values for. For example, to search for game sessions with custom data containing the key:value pair "gameMode:brawl", specify the following: <code>gameSessionProperties.gameMode = "brawl"</code>. All custom data values are searched as strings.</p> </li> <li> <p> <b>maximumSessions</b> -- Maximum number of player sessions allowed for a game session. This value is set when requesting a new game session with <a>CreateGameSession</a> or updating with <a>UpdateGameSession</a>.</p> </li> <li> <p> <b>creationTimeMillis</b> -- Value indicating when a game session was created. It is expressed in Unix time as milliseconds.</p> </li> <li> <p> <b>playerSessionCount</b> -- Number of players currently connected to a game session. This value changes rapidly as players join the session or drop out.</p> </li> <li> <p> <b>hasAvailablePlayerSessions</b> -- Boolean value indicating whether a game session has reached its maximum number of players. It is highly recommended that all search requests include this filter attribute to optimize search performance and return only sessions that players can join. </p> </li> </ul> <note> <p>Returned values for <code>playerSessionCount</code> and <code>hasAvailablePlayerSessions</code> change quickly as players join sessions and others drop out. Results should be considered a snapshot in time. Be sure to refresh search results often, and handle sessions that fill up before a player can join. </p> </note> <p>To search or sort, specify either a fleet ID or an alias ID, and provide a search filter expression, a sort expression, or both. If successful, a collection of <a>GameSession</a> objects matching the request is returned. Use the pagination parameters to retrieve results as a set of sequential pages. </p> <p>You can search for game sessions one fleet at a time only. To find game sessions across multiple fleets, you must search each fleet separately and combine the results. This search feature finds only game sessions that are in <code>ACTIVE</code> status. To locate games in statuses other than active, use <a>DescribeGameSessionDetails</a>.</p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/SearchGameSessions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param searchGameSessionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void SearchGameSessions (
        UObject *WorldContextObject,
        bool &success,
        FSearchGameSessionsRequest searchGameSessionsRequest,
        FSearchGameSessionsResult &searchGameSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Resumes activity on a fleet that was suspended with <a>StopFleetActions</a>. Currently, this operation is used to restart a fleet's auto-scaling activity. </p> <p>To start fleet actions, specify the fleet ID and the type of actions to restart. When auto-scaling fleet actions are restarted, Amazon GameLift once again initiates scaling events as triggered by the fleet's scaling policies. If actions on the fleet were never stopped, this operation will have no effect. You can view a fleet's stopped actions using <a>DescribeFleetAttributes</a>.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StartFleetActions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param startFleetActionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StartFleetActions (
        UObject *WorldContextObject,
        bool &success,
        FStartFleetActionsRequest startFleetActionsRequest,
        FStartFleetActionsResult &startFleetActionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Places a request for a new game session in a queue (see <a>CreateGameSessionQueue</a>). When processing a placement request, Amazon GameLift searches for available resources on the queue's destinations, scanning each until it finds resources or the placement request times out.</p> <p>A game session placement request can also request player sessions. When a new game session is successfully created, Amazon GameLift creates a player session for each player included in the request.</p> <p>When placing a game session, by default Amazon GameLift tries each fleet in the order they are listed in the queue configuration. Ideally, a queue's destinations are listed in preference order.</p> <p>Alternatively, when requesting a game session with players, you can also provide latency data for each player in relevant regions. Latency data indicates the performance lag a player experiences when connected to a fleet in the region. Amazon GameLift uses latency data to reorder the list of destinations to place the game session in a region with minimal lag. If latency data is provided for multiple players, Amazon GameLift calculates each region's average lag for all players and reorders to get the best game play across all players. </p> <p>To place a new game session request, specify the following:</p> <ul> <li> <p>The queue name and a set of game session properties and settings</p> </li> <li> <p>A unique ID (such as a UUID) for the placement. You use this ID to track the status of the placement request</p> </li> <li> <p>(Optional) A set of player data and a unique player ID for each player that you are joining to the new game session (player data is optional, but if you include it, you must also provide a unique ID for each player)</p> </li> <li> <p>Latency data for all players (if you want to optimize game play for the players)</p> </li> </ul> <p>If successful, a new game session placement is created.</p> <p>To track the status of a placement request, call <a>DescribeGameSessionPlacement</a> and check the request's status. If the status is <code>FULFILLED</code>, a new game session has been created and a game session ARN and region are referenced. If the placement request times out, you can resubmit the request or retry it with a different queue. </p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StartGameSessionPlacement">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param startGameSessionPlacementRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StartGameSessionPlacement (
        UObject *WorldContextObject,
        bool &success,
        FStartGameSessionPlacementRequest startGameSessionPlacementRequest,
        FStartGameSessionPlacementResult &startGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Finds new players to fill open slots in an existing game session. This operation can be used to add players to matched games that start with fewer than the maximum number of players or to replace players when they drop out. By backfilling with the same matchmaker used to create the original match, you ensure that new players meet the match criteria and maintain a consistent experience throughout the game session. You can backfill a match anytime after a game session has been created. </p> <p>To request a match backfill, specify a unique ticket ID, the existing game session's ARN, a matchmaking configuration, and a set of data that describes all current players in the game session. If successful, a match backfill ticket is created and returned with status set to QUEUED. The ticket is placed in the matchmaker's ticket pool and processed. Track the status of the ticket to respond as needed. </p> <p>The process of finding backfill matches is essentially identical to the initial matchmaking process. The matchmaker searches the pool and groups tickets together to form potential matches, allowing only one backfill ticket per potential match. Once the a match is formed, the matchmaker creates player sessions for the new players. All tickets in the match are updated with the game session's connection information, and the <a>GameSession</a> object is updated to include matchmaker data on the new players. For more detail on how match backfill requests are processed, see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-match.html"> How Amazon GameLift FlexMatch Works</a>. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-backfill.html"> Backfill Existing Games with FlexMatch</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-match.html"> How GameLift FlexMatch Works</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>StartMatchmaking</a> </p> </li> <li> <p> <a>DescribeMatchmaking</a> </p> </li> <li> <p> <a>StopMatchmaking</a> </p> </li> <li> <p> <a>AcceptMatch</a> </p> </li> <li> <p> <a>StartMatchBackfill</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StartMatchBackfill">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param startMatchBackfillRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StartMatchBackfill (
        UObject *WorldContextObject,
        bool &success,
        FStartMatchBackfillRequest startMatchBackfillRequest,
        FStartMatchBackfillResult &startMatchBackfillResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Uses FlexMatch to create a game match for a group of players based on custom matchmaking rules, and starts a new game for the matched players. Each matchmaking request specifies the type of match to build (team configuration, rules for an acceptable match, etc.). The request also specifies the players to find a match for and where to host the new game session for optimal performance. A matchmaking request might start with a single player or a group of players who want to play together. FlexMatch finds additional players as needed to fill the match. Match type, rules, and the queue used to place a new game session are defined in a <code>MatchmakingConfiguration</code>. </p> <p>To start matchmaking, provide a unique ticket ID, specify a matchmaking configuration, and include the players to be matched. You must also include a set of player attributes relevant for the matchmaking configuration. If successful, a matchmaking ticket is returned with status set to <code>QUEUED</code>. Track the status of the ticket to respond as needed and acquire game session connection information for successfully completed matches.</p> <p> <b>Tracking ticket status</b> -- A couple of options are available for tracking the status of matchmaking requests: </p> <ul> <li> <p>Polling -- Call <code>DescribeMatchmaking</code>. This operation returns the full ticket object, including current status and (for completed tickets) game session connection info. We recommend polling no more than once every 10 seconds.</p> </li> <li> <p>Notifications -- Get event notifications for changes in ticket status using Amazon Simple Notification Service (SNS). Notifications are easy to set up (see <a>CreateMatchmakingConfiguration</a>) and typically deliver match status changes faster and more efficiently than polling. We recommend that you use polling to back up to notifications (since delivery is not guaranteed) and call <code>DescribeMatchmaking</code> only when notifications are not received within 30 seconds.</p> </li> </ul> <p> <b>Processing a matchmaking request</b> -- FlexMatch handles a matchmaking request as follows: </p> <ol> <li> <p>Your client code submits a <code>StartMatchmaking</code> request for one or more players and tracks the status of the request ticket. </p> </li> <li> <p>FlexMatch uses this ticket and others in process to build an acceptable match. When a potential match is identified, all tickets in the proposed match are advanced to the next status. </p> </li> <li> <p>If the match requires player acceptance (set in the matchmaking configuration), the tickets move into status <code>REQUIRES_ACCEPTANCE</code>. This status triggers your client code to solicit acceptance from all players in every ticket involved in the match, and then call <a>AcceptMatch</a> for each player. If any player rejects or fails to accept the match before a specified timeout, the proposed match is dropped (see <code>AcceptMatch</code> for more details).</p> </li> <li> <p>Once a match is proposed and accepted, the matchmaking tickets move into status <code>PLACING</code>. FlexMatch locates resources for a new game session using the game session queue (set in the matchmaking configuration) and creates the game session based on the match data. </p> </li> <li> <p>When the match is successfully placed, the matchmaking tickets move into <code>COMPLETED</code> status. Connection information (including game session endpoint and player session) is added to the matchmaking tickets. Matched players can use the connection information to join the game. </p> </li> </ol> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-client.html"> Add FlexMatch to a Game Client</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-notification.html"> Set Up FlexMatch Event Notification</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-tasks.html"> FlexMatch Integration Roadmap</a> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-match.html"> How GameLift FlexMatch Works</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>StartMatchmaking</a> </p> </li> <li> <p> <a>DescribeMatchmaking</a> </p> </li> <li> <p> <a>StopMatchmaking</a> </p> </li> <li> <p> <a>AcceptMatch</a> </p> </li> <li> <p> <a>StartMatchBackfill</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StartMatchmaking">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param startMatchmakingRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StartMatchmaking (
        UObject *WorldContextObject,
        bool &success,
        FStartMatchmakingRequest startMatchmakingRequest,
        FStartMatchmakingResult &startMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Suspends activity on a fleet. Currently, this operation is used to stop a fleet's auto-scaling activity. It is used to temporarily stop scaling events triggered by the fleet's scaling policies. The policies can be retained and auto-scaling activity can be restarted using <a>StartFleetActions</a>. You can view a fleet's stopped actions using <a>DescribeFleetAttributes</a>.</p> <p>To stop fleet actions, specify the fleet ID and the type of actions to suspend. When auto-scaling fleet actions are stopped, Amazon GameLift no longer initiates scaling events except to maintain the fleet's desired instances setting (<a>FleetCapacity</a>. Changes to the fleet's capacity must be done manually using <a>UpdateFleetCapacity</a>. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StopFleetActions">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param stopFleetActionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StopFleetActions (
        UObject *WorldContextObject,
        bool &success,
        FStopFleetActionsRequest stopFleetActionsRequest,
        FStopFleetActionsResult &stopFleetActionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Cancels a game session placement that is in <code>PENDING</code> status. To stop a placement, provide the placement ID values. If successful, the placement is moved to <code>CANCELLED</code> status.</p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StopGameSessionPlacement">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param stopGameSessionPlacementRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StopGameSessionPlacement (
        UObject *WorldContextObject,
        bool &success,
        FStopGameSessionPlacementRequest stopGameSessionPlacementRequest,
        FStopGameSessionPlacementResult &stopGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Cancels a matchmaking ticket or match backfill ticket that is currently being processed. To stop the matchmaking operation, specify the ticket ID. If successful, work on the ticket is stopped, and the ticket status is changed to <code>CANCELLED</code>.</p> <p>This call is also used to turn off automatic backfill for an individual game session. This is for game sessions that are created with a matchmaking configuration that has automatic backfill enabled. The ticket ID is included in the <code>MatchmakerData</code> of an updated game session object, which is provided to the game server.</p> <note> <p>If the action is successful, the service sends back an empty JSON struct with the HTTP 200 response (not an empty HTTP body).</p> </note> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-client.html"> Add FlexMatch to a Game Client</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>StartMatchmaking</a> </p> </li> <li> <p> <a>DescribeMatchmaking</a> </p> </li> <li> <p> <a>StopMatchmaking</a> </p> </li> <li> <p> <a>AcceptMatch</a> </p> </li> <li> <p> <a>StartMatchBackfill</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/StopMatchmaking">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param stopMatchmakingRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void StopMatchmaking (
        UObject *WorldContextObject,
        bool &success,
        FStopMatchmakingRequest stopMatchmakingRequest,
        FStopMatchmakingResult &stopMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates properties for an alias. To update properties, specify the alias ID to be updated and provide the information to be changed. To reassign an alias to another fleet, provide an updated routing strategy. If successful, the updated alias record is returned.</p> <ul> <li> <p> <a>CreateAlias</a> </p> </li> <li> <p> <a>ListAliases</a> </p> </li> <li> <p> <a>DescribeAlias</a> </p> </li> <li> <p> <a>UpdateAlias</a> </p> </li> <li> <p> <a>DeleteAlias</a> </p> </li> <li> <p> <a>ResolveAlias</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateAlias">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateAliasRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateAlias (
        UObject *WorldContextObject,
        bool &success,
        FGameLiftUpdateAliasRequest updateAliasRequest,
        FGameLiftUpdateAliasResult &updateAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates metadata in a build record, including the build name and version. To update the metadata, specify the build ID to update and provide the new values. If successful, a build object containing the updated metadata is returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/build-intro.html"> Working with Builds</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateBuild</a> </p> </li> <li> <p> <a>ListBuilds</a> </p> </li> <li> <p> <a>DescribeBuild</a> </p> </li> <li> <p> <a>UpdateBuild</a> </p> </li> <li> <p> <a>DeleteBuild</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateBuild">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateBuildRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateBuild (
        UObject *WorldContextObject,
        bool &success,
        FUpdateBuildRequest updateBuildRequest,
        FUpdateBuildResult &updateBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates fleet properties, including name and description, for a fleet. To update metadata, specify the fleet ID and the property values that you want to change. If successful, the fleet ID for the updated fleet is returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateFleetAttributes">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateFleetAttributesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateFleetAttributes (
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetAttributesRequest updateFleetAttributesRequest,
        FUpdateFleetAttributesResult &updateFleetAttributesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates capacity settings for a fleet. Use this action to specify the number of EC2 instances (hosts) that you want this fleet to contain. Before calling this action, you may want to call <a>DescribeEC2InstanceLimits</a> to get the maximum capacity based on the fleet's EC2 instance type.</p> <p>Specify minimum and maximum number of instances. Amazon GameLift will not change fleet capacity to values fall outside of this range. This is particularly important when using auto-scaling (see <a>PutScalingPolicy</a>) to allow capacity to adjust based on player demand while imposing limits on automatic adjustments.</p> <p>To update fleet capacity, specify the fleet ID and the number of instances you want the fleet to host. If successful, Amazon GameLift starts or terminates instances so that the fleet's active instance count matches the desired instance count. You can view a fleet's current capacity information by calling <a>DescribeFleetCapacity</a>. If the desired instance count is higher than the instance type's limit, the "Limit Exceeded" exception occurs.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateFleetCapacity">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateFleetCapacityRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateFleetCapacity (
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetCapacityRequest updateFleetCapacityRequest,
        FUpdateFleetCapacityResult &updateFleetCapacityResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates port settings for a fleet. To update settings, specify the fleet ID to be updated and list the permissions you want to update. List the permissions you want to add in <code>InboundPermissionAuthorizations</code>, and permissions you want to remove in <code>InboundPermissionRevocations</code>. Permissions to be removed must match existing fleet permissions. If successful, the fleet ID for the updated fleet is returned.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateFleetPortSettings">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateFleetPortSettingsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateFleetPortSettings (
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetPortSettingsRequest updateFleetPortSettingsRequest,
        FUpdateFleetPortSettingsResult &updateFleetPortSettingsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates game session properties. This includes the session name, maximum player count, protection policy, which controls whether or not an active game session can be terminated during a scale-down event, and the player session creation policy, which controls whether or not new players can join the session. To update a game session, specify the game session ID and the values you want to change. If successful, an updated <a>GameSession</a> object is returned. </p> <ul> <li> <p> <a>CreateGameSession</a> </p> </li> <li> <p> <a>DescribeGameSessions</a> </p> </li> <li> <p> <a>DescribeGameSessionDetails</a> </p> </li> <li> <p> <a>SearchGameSessions</a> </p> </li> <li> <p> <a>UpdateGameSession</a> </p> </li> <li> <p> <a>GetGameSessionLogUrl</a> </p> </li> <li> <p>Game session placements</p> <ul> <li> <p> <a>StartGameSessionPlacement</a> </p> </li> <li> <p> <a>DescribeGameSessionPlacement</a> </p> </li> <li> <p> <a>StopGameSessionPlacement</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateGameSession">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateGameSessionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateGameSession (
        UObject *WorldContextObject,
        bool &success,
        FUpdateGameSessionRequest updateGameSessionRequest,
        FUpdateGameSessionResult &updateGameSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates settings for a game session queue, which determines how new game session requests in the queue are processed. To update settings, specify the queue name to be updated and provide the new settings. When updating destinations, provide a complete list of destinations. </p> <ul> <li> <p> <a>CreateGameSessionQueue</a> </p> </li> <li> <p> <a>DescribeGameSessionQueues</a> </p> </li> <li> <p> <a>UpdateGameSessionQueue</a> </p> </li> <li> <p> <a>DeleteGameSessionQueue</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateGameSessionQueue">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateGameSessionQueueRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateGameSessionQueue (
        UObject *WorldContextObject,
        bool &success,
        FUpdateGameSessionQueueRequest updateGameSessionQueueRequest,
        FUpdateGameSessionQueueResult &updateGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates settings for a FlexMatch matchmaking configuration. These changes affect all matches and game sessions that are created after the update. To update settings, specify the configuration name to be updated and provide the new settings. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-configuration.html"> Design a FlexMatch Matchmaker</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateMatchmakingConfiguration">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateMatchmakingConfigurationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateMatchmakingConfiguration (
        UObject *WorldContextObject,
        bool &success,
        FUpdateMatchmakingConfigurationRequest updateMatchmakingConfigurationRequest,
        FUpdateMatchmakingConfigurationResult &updateMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates the current run-time configuration for the specified fleet, which tells Amazon GameLift how to launch server processes on instances in the fleet. You can update a fleet's run-time configuration at any time after the fleet is created; it does not need to be in an <code>ACTIVE</code> status.</p> <p>To update run-time configuration, specify the fleet ID and provide a <code>RuntimeConfiguration</code> object with an updated set of server process configurations.</p> <p>Each instance in a Amazon GameLift fleet checks regularly for an updated run-time configuration and changes how it launches server processes to comply with the latest version. Existing server processes are not affected by the update; run-time configuration changes are applied gradually as existing processes shut down and new processes are launched during Amazon GameLift's normal process recycling activity.</p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/fleets-intro.html"> Working with Fleets</a>.</p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateFleet</a> </p> </li> <li> <p> <a>ListFleets</a> </p> </li> <li> <p> <a>DeleteFleet</a> </p> </li> <li> <p>Describe fleets:</p> <ul> <li> <p> <a>DescribeFleetAttributes</a> </p> </li> <li> <p> <a>DescribeFleetCapacity</a> </p> </li> <li> <p> <a>DescribeFleetPortSettings</a> </p> </li> <li> <p> <a>DescribeFleetUtilization</a> </p> </li> <li> <p> <a>DescribeRuntimeConfiguration</a> </p> </li> <li> <p> <a>DescribeEC2InstanceLimits</a> </p> </li> <li> <p> <a>DescribeFleetEvents</a> </p> </li> </ul> </li> <li> <p>Update fleets:</p> <ul> <li> <p> <a>UpdateFleetAttributes</a> </p> </li> <li> <p> <a>UpdateFleetCapacity</a> </p> </li> <li> <p> <a>UpdateFleetPortSettings</a> </p> </li> <li> <p> <a>UpdateRuntimeConfiguration</a> </p> </li> </ul> </li> <li> <p>Manage fleet actions:</p> <ul> <li> <p> <a>StartFleetActions</a> </p> </li> <li> <p> <a>StopFleetActions</a> </p> </li> </ul> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateRuntimeConfiguration">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateRuntimeConfigurationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateRuntimeConfiguration (
        UObject *WorldContextObject,
        bool &success,
        FUpdateRuntimeConfigurationRequest updateRuntimeConfigurationRequest,
        FUpdateRuntimeConfigurationResult &updateRuntimeConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Updates Realtime script metadata and content.</p> <p>To update script metadata, specify the script ID and provide updated name and/or version values. </p> <p>To update script content, provide an updated zip file by pointing to either a local file or an Amazon S3 bucket location. You can use either method regardless of how the original script was uploaded. Use the <i>Version</i> parameter to track updates to the script.</p> <p>If the call is successful, the updated metadata is stored in the script record and a revised script is uploaded to the Amazon GameLift service. Once the script is updated and acquired by a fleet instance, the new version is used for all new game sessions. </p> <p> <b>Learn more</b> </p> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/realtime-intro.html">Amazon GameLift Realtime Servers</a> </p> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateScript</a> </p> </li> <li> <p> <a>ListScripts</a> </p> </li> <li> <p> <a>DescribeScript</a> </p> </li> <li> <p> <a>UpdateScript</a> </p> </li> <li> <p> <a>DeleteScript</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/UpdateScript">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param updateScriptRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void UpdateScript (
        UObject *WorldContextObject,
        bool &success,
        FUpdateScriptRequest updateScriptRequest,
        FUpdateScriptResult &updateScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  <p>Validates the syntax of a matchmaking rule or rule set. This operation checks that the rule set is using syntactically correct JSON and that it conforms to allowed property expressions. To validate syntax, provide a rule set JSON string.</p> <p> <b>Learn more</b> </p> <ul> <li> <p> <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-rulesets.html">Build a Rule Set</a> </p> </li> </ul> <p> <b>Related operations</b> </p> <ul> <li> <p> <a>CreateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DescribeMatchmakingConfigurations</a> </p> </li> <li> <p> <a>UpdateMatchmakingConfiguration</a> </p> </li> <li> <p> <a>DeleteMatchmakingConfiguration</a> </p> </li> <li> <p> <a>CreateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DescribeMatchmakingRuleSets</a> </p> </li> <li> <p> <a>ValidateMatchmakingRuleSet</a> </p> </li> <li> <p> <a>DeleteMatchmakingRuleSet</a> </p> </li> </ul><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/gamelift-2015-10-01/ValidateMatchmakingRuleSet">AWS API Reference</a></p>
    *  Queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param validateMatchmakingRuleSetRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "GameLift Client")
    void ValidateMatchmakingRuleSet (
        UObject *WorldContextObject,
        bool &success,
        FValidateMatchmakingRuleSetRequest validateMatchmakingRuleSetRequest,
        FValidateMatchmakingRuleSetResult &validateMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
};
