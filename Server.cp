using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;

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

                string response = ProcessRequest(request);

                byte[] responseData = Encoding.ASCII.GetBytes(response);
                serverSocket.Send(responseData, responseData.Length, clientEndPoint);

                Console.WriteLine($"Response sent to {clientEndPoint}: {response}");
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
            return "Keine Price, koroche ti chtoto ponajimal: " + request;
        }
    }
}
