using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using System.Threading;

class UDPServer
{
    static Dictionary<string, string> componentPrices = new Dictionary<string, string>()
    {
        { "processor", "$200" },
        { "motherboard", "$150" },
        { "ram", "$80" },
        { "graphics card", "$300" },
        { "storage", "$100" }
    };

    static Dictionary<string, int> clientRequestsCount = new Dictionary<string, int>();
    const int MaxRequestsPerHour = 10;

    static void Main(string[] args)
    {
        int serverPort = 20042;
        UdpClient serverSocket = new UdpClient(serverPort);

        Console.WriteLine("Server started...");

        try
        {
            while (true)
            {
                IPEndPoint clientEndPoint = new IPEndPoint(IPAddress.Any, 0);
                byte[] data = serverSocket.Receive(ref clientEndPoint);
                string request = Encoding.ASCII.GetString(data);

                string clientKey = $"{clientEndPoint.Address}:{clientEndPoint.Port}";
                if (!clientRequestsCount.ContainsKey(clientKey))
                {
                    clientRequestsCount.Add(clientKey, 0);
                }

                if (clientRequestsCount[clientKey] >= MaxRequestsPerHour)
                {
                    serverSocket.Send(Encoding.ASCII.GetBytes("LIMIT"), "LIMIT".Length, clientEndPoint);
                    continue;
                }

                string response = ProcessRequest(request);
                byte[] responseData = Encoding.ASCII.GetBytes(response);
                serverSocket.Send(responseData, responseData.Length, clientEndPoint);

                Console.WriteLine($"Response sent to {clientEndPoint}: {response}");

                clientRequestsCount[clientKey]++;
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error: {ex.Message}");
        }
        finally
        {
            serverSocket.Close();
        }
    }

    static string ProcessRequest(string request)
    {
        if (componentPrices.ContainsKey(request.ToLower()))
        {
            return componentPrices[request.ToLower()];
        }
        else
        {
            return "Chto-to ne to: " + request;
        }
    }
}
