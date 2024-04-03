UDP Networking Example
======================

.. caution::
    No Production/Ready to use code is provided here, this is just code to show how networking with amethyst can be done.

.. line-block::
    Minecraft Bedrock Edition is an uwp (Universal Windows Platform) app, that means it is mostly sandboxed and doesn't have access to most windows apis.
    We normally use a windows lib like winsock for windows to connected to/create servers.
    But due to it being an uwp app, we need to use the winrt.

.. highlight:: cpp
    :linenothreshold: 1
    :force:

.. code-block:: cpp

    winrt::Windows::Foundation::IAsyncAction send_packet(std::string data)
    {
        try
        {
            // If the socket is not already connected, connect to the local server on port 12345
            if (!local_socket.Information().LocalAddress())
        {
            co_await local_socket.ConnectAsync(winrt::Windows::Networking::HostName(L"127.0.0.1"), L"12345");
        }

        // Create a message to send
        std::wstring message(data.begin(), data.end());
        winrt::Windows::Storage::Streams::DataWriter writer;
        writer.WriteString(message);

        // Send the message
        co_await local_socket.OutputStream().WriteAsync(writer.DetachBuffer());

        writer.Close();

        std::wcout << L"Message sent successfully!" << std::endl;
        }
            catch (winrt::hresult_error const& ex)
        {
            std::wcerr << L"Error: " << ex.message().c_str() << std::endl;
        }
    }