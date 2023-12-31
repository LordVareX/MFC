﻿/*
* Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#pragma once
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/cognito-idp/model/DeviceType.h>
#include <utility>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace CognitoIdentityProvider
{
namespace Model
{
  /**
   * <p>Represents the response to list devices.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/cognito-idp-2016-04-18/ListDevicesResponse">AWS
   * API Reference</a></p>
   */
  class AWS_COGNITOIDENTITYPROVIDER_API ListDevicesResult
  {
  public:
    ListDevicesResult();
    ListDevicesResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    ListDevicesResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);


    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline const Aws::Vector<DeviceType>& GetDevices() const{ return m_devices; }

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline void SetDevices(const Aws::Vector<DeviceType>& value) { m_devices = value; }

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline void SetDevices(Aws::Vector<DeviceType>&& value) { m_devices = std::move(value); }

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline ListDevicesResult& WithDevices(const Aws::Vector<DeviceType>& value) { SetDevices(value); return *this;}

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline ListDevicesResult& WithDevices(Aws::Vector<DeviceType>&& value) { SetDevices(std::move(value)); return *this;}

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline ListDevicesResult& AddDevices(const DeviceType& value) { m_devices.push_back(value); return *this; }

    /**
     * <p>The devices returned in the list devices response.</p>
     */
    inline ListDevicesResult& AddDevices(DeviceType&& value) { m_devices.push_back(std::move(value)); return *this; }


    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline const Aws::String& GetPaginationToken() const{ return m_paginationToken; }

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline void SetPaginationToken(const Aws::String& value) { m_paginationToken = value; }

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline void SetPaginationToken(Aws::String&& value) { m_paginationToken = std::move(value); }

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline void SetPaginationToken(const char* value) { m_paginationToken.assign(value); }

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline ListDevicesResult& WithPaginationToken(const Aws::String& value) { SetPaginationToken(value); return *this;}

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline ListDevicesResult& WithPaginationToken(Aws::String&& value) { SetPaginationToken(std::move(value)); return *this;}

    /**
     * <p>The pagination token for the list device response.</p>
     */
    inline ListDevicesResult& WithPaginationToken(const char* value) { SetPaginationToken(value); return *this;}

  private:

    Aws::Vector<DeviceType> m_devices;

    Aws::String m_paginationToken;
  };

} // namespace Model
} // namespace CognitoIdentityProvider
} // namespace Aws
